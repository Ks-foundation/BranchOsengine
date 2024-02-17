// cani.js

function animateFrames(frames, frameRate) {
    let index = 0;
    const interval = setInterval(() => {
        process.stdout.clearLine();  // 현재 줄을 지웁니다.
        process.stdout.cursorTo(0);  // 커서를 줄의 시작점으로 이동합니다.
        process.stdout.write(frames[index % frames.length]);  // 프레임의 내용을 출력합니다.
        index++;
        if (index >= frames.length) {
            clearInterval(interval);  // 애니메이션 종료
            console.log();  // 다음 출력을 위해 줄 바꿈
        }
    }, 1000 / frameRate);  // 1초를 frameRate로 나눈 값만큼의 간격으로 출력
}

module.exports = { animateFrames };
