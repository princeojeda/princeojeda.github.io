window.onload = function () {
    const formPG = document.getElementById('pg-form');
    const formIG = document.getElementById('ig-form');
    const formTT = document.getElementById('tt-form');

    formPG.addEventListener('submit', function (event) {
        event.preventDefault();
        const passInput = document.getElementById('password');
        passInput.value = generateRandomPassword(12);
        passInput.onclick = function () {
            this.select();
            document.execCommand('copy');
        }

    });
    formIG.addEventListener('submit', function (event) {
        event.preventDefault();
        const formData = new FormData(formIG);
        const data = Object.fromEntries(formData.entries());
        console.log('IG Form Data:', data);
    });

    formTT.addEventListener('submit', function (event) {
        event.preventDefault();
        const urlInput = document.getElementById('tt-url');
        const url = urlInput.value.trim();
        if (url) {
            downloadTiktokVideo(url);
        } else {
            alert('Please enter a valid TikTok video URL.');
        }
    });
}

function generateRandomPassword(length) {
    const charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-=_+~`{}[]:\";',.<>/?|\\";
    let password = "";
    for (let i = 0; i < length; i++) {
        const randomIndex = Math.floor(Math.random() * charset.length);
        password += charset[randomIndex];
    }
    return password;
}

function downloadTiktokVideo(url) {
    const downloadUrl = `https://ssstik.io/abc?url=dl`;

    fetch(downloadUrl, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
            'Origin': 'https://ssstik.io',
            'Referer': 'https://ssstik.io/',
            'sec-fetch-dest': 'empty',
            'sec-fetch-mode': 'cors',
            'sec-fetch-site': 'same-origin',
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3'
        },
        body: JSON.stringify({
            id: url,
            locale: 'en',
            tt: 'MmVDdEU2'
        })
    })
        .then(response => response.text())
        .then(data => {
            const woutwm = data.match(/<a\s+[^>]*href="([^"]+)"[^>]*>[^<]*Without watermark[^<]*<\/a>/i);
            if (woutwm && woutwm[1]) {
                const videoUrl = woutwm[1];

                fetch(videoUrl)
                    .then(response => {
                        if (!response.ok) {
                            throw new Error('Network response was not ok');
                        }
                        return response.blob();
                    })
                    .then(blob => {
                        const url = URL.createObjectURL(blob);
                        const link = document.createElement('a');
                        link.href = url;
                        link.download = 'tiktok_video.mp4';
                        document.body.appendChild(link);
                        link.click();
                        document.body.removeChild(link);
                        URL.revokeObjectURL(url);
                    })
                    .catch(error => console.error('Error downloading video:', error));
            } else {
                console.error('No video URL found in the response.');
            }
        })
        .catch(error => console.error('Error downloading video:', error));
}
