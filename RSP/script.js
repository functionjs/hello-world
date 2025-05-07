var playerScore = 0;
var botScore = 0;
var roundsLeft = 0;
var totalRounds = 5;
var playerName = '';
var botStrength = 0;
var gamesCount = 0;
var playerHistory = [];


const gameSettings = document.querySelector('.settings'); 
const gamePanel= document.querySelector('.game')

const playerNameTag = document.getElementById('playerName')
const totalRoundsTag = document.getElementById('totalRounds')
const botStrengthTag = document.getElementById('botStrength')

const botChoiceTag = document.getElementById('botChoice')
const resultTag    = document.getElementById('result')    

const playerScoreTag = document.getElementById('playerScore')
const botScoreTag = document.getElementById('botScore')
const roundsLeftTag = document.getElementById('roundsLeft')


        ///////////////////////#startGame onclick()
        function startGame() {
            playerName  = playerNameTag.value;
            totalRounds = parseInt(totalRoundsTag.value);
            botStrength = parseInt(botStrengthTag.value);
            
            // Load player history from localStorage
            const savedData = localStorage.getItem(playerName);
            clearHistoryTag.innerHTML = ""
             if (savedData) {
                playerHistory = JSON.parse(savedData);
                if(playerHistory[0])
                   clearHistoryTag.innerHTML = "You can  clear Your moves history ... ";
             }else 
              
             botChoiceTag.textContent = `Bot chose: ...`; 
             resultTag.textContent = "?";
             gamePanel.style.visibility = 'visible';
             document.querySelector('.game').style.visibility = 'visible';
             gameSettings.style.visibility = 'hidden';
             roundsLeft = totalRounds;
              updateScores();
        }
             function clearHistory(){
               // Clear player history in localStorage
                localStorage.setItem(playerName, JSON.stringify([]));
                clearHistoryTag.innerHTML = "Your moves history cleared 🧹";
             } 

var choices = ['rock 🪨', 'paper 📰', 'scissors ✂'];
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
                let botChoiceTag = document.getElementById('botChoice')
                 botChoiceTag.textContent = `Bot chose: ${botChoice}`;
                  botChoiceTag.style.transform += 'rotateX(360deg)';
             
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
               //let resultTag=document.getElementById('result')       
                resultTag.textContent = result;
                resultTag.style.transform += 'rotate(360deg)';
                
              updateScores();
              
              // Check game end
              if (roundsLeft === 0)
                  setTimeout(currentGameEnd, 3000);
                  function currentGameEnd(){
                                            // Save player history to localStorage
                                            localStorage.setItem(playerName, JSON.stringify(playerHistory));
                                            //Increase count of Games                 
                                            gamesCount++;
                                             let message = 'Game '+gamesCount+": ";
                                              if (playerScore > botScore)message += `Congratulations ${playerName}! You (👧) won the game!`;
                                              else if (botScore > playerScore)message += 'Bot (🤖) wins the game! Better luck next time!';
                                                   else message += "It's a draw!";
                                             
                                               myconsole.innerHTML += message+"\n";
                                                setTimeout(displayRotatedGameSettings, 1000);
                                                  function displayRotatedGameSettings(){
                                                            //let gameSettings=document.querySelector('.settings'); 
                                                             gameSettings.style.visibility = 'visible';
                                                             gameSettings.style.transform += 'rotateX(360deg)';
                                                  }
                                               
                                               // Reset game
                                               playerScore = botScore = 0;
                                               //let gamePanel= document.querySelector('.game')
                                               // gamePanel.style.transform += 'rotateX(360deg)';
                                               gamePanel.style.visibility = 'hidden';
                                                updateScores();
               
                 }
        }       

            function updateScores() {
                playerScoreTag.textContent = playerScore;
                botScoreTag.textContent = botScore;
                roundsLeftTag.textContent = roundsLeft;
            }
