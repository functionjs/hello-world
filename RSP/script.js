var playerScore = 0;
var botScore = 0;
var roundsLeft = 0;
var totalRounds = 5;
var playerName = '';
var botStrength = 0;
var gamesCount = 0;
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

const choices = ['rock 🪨', 'paper 📰', 'scissors ✂'];
        ///////////////////
        function getBotChoice() {
           let random = Math.floor(Math.random() * 3); 
            if (botStrength === 0)return choices[0];; // Weakest bot - always chooses rock
            if (botStrength === 1)return choices[random]; // Medium bot - random choice
            //if (botStrength === 2) Strongest bot
            if (playerHistory.length === 0) return choices[random]; //if history is empty then Strongest bot uses player random choice
            
            // Strongest bot calculate the most frequent player choice
            const counts = {rock: 0, paper: 0, scissors: 0};
             playerHistory.forEach(choice => counts[choice]++);
             //console.log("before sorting Object.entries(counts)");
             //console.dir(Object.entries(counts));
              const mostFrequent = Object.entries(counts).sort((a, b) => b[1] - a[1])[0][0];
               //console.log("after sorting Object.entries(counts)");
               //console.dir(Object.entries(counts));
                //console.log("mostFrequent = ",mostFrequent)
              // Choose counter to most frequent
               return {
                        rock: choices[2],
                        paper: choices[1],
                        scissors: choices[0]
                      }[mostFrequent];
        }
        /////////////////////////////
        function play(playerChoice) {
            if (roundsLeft <= 0) return;
            roundsLeft--;
               // Save player choice for strongest bot
               playerHistory.push(playerChoice);
                const botChoice = getBotChoice();
                 document.getElementById('botChoice').textContent = `Bot chose: ${botChoice}`;
                 document.getElementById('botChoice').style.transform += 'rotateX(360deg)';
             
              // Determine winner
            let result = 'In round '+ (totalRounds - roundsLeft) + " ";
              if (playerChoice === botChoice) {
                result += '⚖ Draw!';
              }
              else if(
                       (playerChoice === choices[0] && botChoice === choices[1]) ||
                       (playerChoice === choices[1] && botChoice === choices[2])    ||
                       (playerChoice === choices[2] && botChoice === choices[0])
                     ){
                       result += '👧 Player wins!';
                       playerScore++;
                      }
                 else {
                       result += '🤖 Bot wins!';
                       botScore++;
                      }
               document.getElementById('result').textContent = result;
               document.getElementById('result').style.transform += 'rotate(360deg)';
                
              updateScores();
              
           
               // Check game end
               if (roundsLeft === 0) {
                  // Save player history to localStorage
                  localStorage.setItem(playerName, JSON.stringify(playerHistory));
                  //Increase count of Games                 
                  gamesCount++;
                   let message = 'Game '+gamesCount+": ";
                     if (playerScore > botScore)message += `Congratulations ${playerName}! You (👧) won the game!`;
                     else if (botScore > playerScore)message += 'Bot (🤖) wins the game! Better luck next time!';
                          else message += "It's a draw!";
                            
                      myconsole.innerHTML += message+"\n";
                      //alert(message);
                      document.querySelector('.settings').style.display = 'block';
                      document.querySelector('.settings').style.transform += 'rotateX(360deg)';
                      // Reset game
                      playerScore = botScore = 0;
                      document.querySelector('.game').style.transform += 'rotateX(360deg)';
                      //document.querySelector('.game').style.display = 'none';
                      updateScores();
                }
        }

            function updateScores() {
                document.getElementById('playerScore').textContent = playerScore;
                document.getElementById('botScore').textContent = botScore;
                document.getElementById('roundsLeft').textContent = roundsLeft;
            }
