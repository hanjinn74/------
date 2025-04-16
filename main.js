function randomize() {
  const colors = ["#FF5733", "#33FF57", "#3357FF", "#F3FF33", "#FF33F3"];
  const messages = [
    "오늘도 멋진 하루!",
    "코딩은 재미있어요!",
    "웹 개발, 화이팅!",
    "CSS는 예술입니다!",
    "JavaScript는 마법 같아요!"
  ];

  // 랜덤 색상과 메시지 선택
  const randomColor = colors[Math.floor(Math.random() * colors.length)];
  const randomMessage = messages[Math.floor(Math.random() * messages.length)];

  // 배경색 변경
  document.body.style.backgroundColor = randomColor;

  // 메시지 표시
  const messageDiv = document.getElementById("fun-message");
  messageDiv.textContent = randomMessage;
}