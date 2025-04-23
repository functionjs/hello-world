var playerScore = 0;
var botScore = 0;
var roundsLeft = 0;
var totalRounds = 5;
var playerName = '';
var botStrength = 0;
var playerHistory = [];

        ///////////////////////#startGame onclick()
        function startGame() {
            playerName = document.getElementById('playerName').value;
            totalRounds = parseInt(document.getElementById('totalRounds').value);
            botStrength = parseInt(document.getElementById('botStrength').value);
            
            // Load player history from localStorage
            const savedData = localStorage.getItem(playerName);
             if (savedData) {
                playerHistory = JSON.parse(savedData);
             }
            
             document.getElementById('botChoice').textContent = `Bot chose: ...`; 
             document.getElementById('result').textContent = "?";
             document.querySelector('.game').style.display = 'block';
             document.querySelector('.settings').style.display = 'none';
             roundsLeft = totalRounds;
              updateScores();
        }

const choices = ['rock', 'paper', 'scissors'];
        ///////////////////
        function getBotChoice() {
            if (botStrength === 0) { // Weakest bot - always chooses rock
                return 'rock';
            }
            
            if (botStrength === 1) { // Medium bot - random choice
                 return choices[Math.floor(Math.random() * 3)];
            }
            
            // Strongest bot - uses player history
            if (playerHistory.length === 0) {
                return choices[Math.floor(Math.random() * 3)];
            }
            
            // Calculate most frequent player choice
            const counts = {rock: 0, paper: 0, scissors: 0};
             playerHistory.forEach(choice => counts[choice]++);
             console.log("before sorting Object.entries(counts)");
             console.dir(Object.entries(counts));
              const mostFrequent = Object.entries(counts).sort((a, b) => b[1] - a[1])[0][0];
               console.log("after sorting Object.entries(counts)");
               console.dir(Object.entries(counts));
                console.log("mostFrequent = ",mostFrequent)
              // Choose counter to most frequent
               return {
                        rock: 'paper',
                        paper: 'scissors',
                        scissors: 'rock'
                      }[mostFrequent];
        }
        /////////////////////////////
        function play(playerChoice) {
            if (roundsLeft <= 0) return;
            
            const botChoice = getBotChoice();
            document.getElementById('botChoice').textContent = `Bot chose: ${botChoice}`;
            
            // Save player choice for strongest bot
            playerHistory.push(playerChoice);
            
            // Determine winner
            let result = '';
            if (playerChoice === botChoice) {
                result = 'Draw!';
            }
            else if (
                     (playerChoice === 'rock' && botChoice === 'scissors') ||
                     (playerChoice === 'paper' && botChoice === 'rock') ||
                     (playerChoice === 'scissors' && botChoice === 'paper')
                    ) {
                       result = 'Player wins!';
                       playerScore++;
                      }
                 else {
                       result = 'Bot wins!';
                       botScore++;
                      }
            
            document.getElementById('result').textContent = result;
            roundsLeft--;
            updateScores();
            
            // Check game end
            if (roundsLeft === 0) {
                let message = '';
                if (playerScore > botScore) {
                    message = `Congratulations ${playerName}! You won the game!`;
                } else if (botScore > playerScore) {
                    message = 'Bot wins the game! Better luck next time!';
                } else {
                    message = "It's a draw!";
                }
                myconsole.innerHTML += message+"\n";
                //alert(message);
                document.querySelector('.settings').style.display = 'block';
                // Save player history to localStorage
                localStorage.setItem(playerName, JSON.stringify(playerHistory));
                
                // Reset game
                playerScore = botScore = 0;
                document.querySelector('.game').style.display = 'none';
            }
        }

            function updateScores() {
                document.getElementById('playerScore').textContent = playerScore;
                document.getElementById('botScore').textContent = botScore;
                document.getElementById('roundsLeft').textContent = roundsLeft;
            }