const cells = document.querySelectorAll('[data-cell]');
const statusText = document.getElementById('status');
const restartBtn = document.getElementById('restart');
let xTurn = true;

const winPatterns = [
    [0,1,2], [3,4,5], [6,7,8], [0,3,6], [1,4,7], [2,5,8], [0,4,8], [2,4,6]
];

cells.forEach(cell => {
    cell.addEventListener('click', handleClick, { once: true });
});

function handleClick(e) {
    const cell = e.target;
    const currentClass = xTurn ? 'x' : 'o';
    cell.innerText = currentClass.toUpperCase();
    cell.classList.add(currentClass);
    
    if (checkWin(currentClass)) {
        statusText.innerText = `Player ${currentClass.toUpperCase()} Wins! 🎉`;
    } else if (isDraw()) {
        statusText.innerText = "It's a Draw! 🤝";
    } else {
        xTurn = !xTurn;
        statusText.innerText = `Player ${xTurn ? 'X' : 'O'}'s Turn`;
    }
}

function checkWin(currentClass) {
    return winPatterns.some(pattern => {
        return pattern.every(index => cells[index].classList.contains(currentClass));
    });
}

function isDraw() {
    return [...cells].every(cell => cell.innerText !== '');
}

restartBtn.addEventListener('click', () => location.reload());
