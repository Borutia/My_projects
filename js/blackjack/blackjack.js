/*eslint-env browser*/        
        var suits = ["Spades", "Hearts", "Diamonds", "Clubs"];
        var values = ["3","5","7","9","K","Q","10","J","A","8","6","4","2"]
        var deck = new Array();
        var players = new Array();
        var currentPlayer = 0;

        function createDeck()
        {
            deck = new Array();
            for (var i = 0 ; i < values.length; i++)
            {
                for(var x = 0; x < suits.length; x++)
                {
                    var weight = parseInt(values[i]);
                    if (values[i] == "J" || values[i] == "Q" || values[i] == "K")
                        weight = 10;
                    if (values[i] == "A")
                        weight = 11;
                    var card = 
						{ 
						Value: values[i], 
                        Suit: suits[x],
                        Weight: weight 
					};
                    deck.push(card);
                }
            }
        }

        function uniform_random()
        {
            var result = 1 + Math.floor(Math.random() * (suits.length));
            return result;
        }

       
        
        function hitMe()
        {
            var card_suits = uniform_random();
            var card_values = triangular_random();
            var weight = parseInt(values[card_values]);
                    if (values[card_values] == "J" || values[card_values] == "Q" || values[card_values] == "K")
                        weight = 10;
                    if (values[card_values] == "A")
                        weight = 11;
                    var card = 
						{ 
						Value: values[card_values], 
                        Suit: suits[card_suits],
                        Weight: weight 
					};
            var test_deck = new Array();
            test_deck.push(card);
            var count = 0
            for(var i = 0; i< deck.length; i++)
                {
                    if(deck[i].Suit == test_deck[0].Suit && deck[i].Value == test_deck[0].Value)
                        {
                         var temp = deck[i];
                         deck[i] = deck[deck.length-1];
                         deck[deck.length-1] = temp;
                         var card_del = deck.pop();
                         players[currentPlayer].Hand.push(card_del);
                         renderCard(card_del, currentPlayer);
                         updatePoints();
                         updateDeck();
                         nextcard();
                         check();
                         count++;
                         break;
                        }
                    
                }
           if (count==0)
               {
                   hitMe();
               }
             
        }
        function nextcard()
        {
            var card_values = triangular_random();
            var weight = values[card_values];
             if (values[card_values] == "J" || values[card_values] == "Q" || values[card_values] == "K")
                        weight = 10;
                    if (values[card_values] == "A")
                        weight = 11;
            document.getElementById('next_card').innerHTML = weight;
            document.getElementById('next_card').style.display = "inline-block";
        }
        
        function first_cards()
        {
            hitMe();
            
            currentPlayer++;
            hitMe();
            hitMe();
            currentPlayer--;
        }

        function bot()
        {
            hitMe();
            if(players[currentPlayer].Points <=16)
                {
                    while(players[currentPlayer].Points <=16)
                        {
                            hitMe();
                        }
                    stay();
                }
            else
                {
                    stay();
                }
        }

        function triangular_random()
        {
            var result = Math.floor((Math.floor(Math.random() * (values.length)) + Math.floor(Math.random() * (values.length)))/2);
            return result;
        }

        function createPlayers(num)
        {
            players = new Array();
            for(var i = 1; i <= num; i++)
            {
                var hand = new Array();
                var player = 
                    {
                        Name: 'Player ' + i, 
                        ID: i, 
                        Points: 0, 
                        Hand: hand 
                    };
                players.push(player);
            }
        }

        function startblackjack()
        {
            document.getElementById("STOP").disabled = false;
            document.getElementById("STOP1").disabled = false;
            document.getElementById('btnStart').value = 'Заново';
            document.getElementById("status").style.display="none";
            currentPlayer = 0;
            createDeck();
            createPlayers(2);
            createPlayersUI();
            document.getElementById('deckcount').style.display = "inline-block";
            first_cards();
            bot();
            document.getElementById('player_' + currentPlayer).classList.add('active');
            nextcard();
            check();
        }

        function createPlayersUI()
        {
            document.getElementById('players').innerHTML = '';
            for(var i = 0; i < players.length; i++)
            {
                var div_player = document.createElement('div');
                var div_playerid = document.createElement('div');
                var div_hand = document.createElement('div');
                var div_points = document.createElement('div');

                div_points.className = 'points';
                div_points.id = 'points_' + i;
                div_player.id = 'player_' + i;
                div_player.className = 'player';
                div_hand.id = 'hand_' + i;
                if(i==0)
                    {
                    div_playerid.innerHTML = 'Дилер';
                    }
                else
                {
                    div_playerid.innerHTML = 'Игрок';
                }
                div_player.appendChild(div_playerid);
                div_player.appendChild(div_hand);
                div_player.appendChild(div_points);
                document.getElementById('players').appendChild(div_player);
            }
        }
        function renderCard(card, player)
        {
            var hand = document.getElementById('hand_' + player);
            hand.appendChild(getCardUI(card));
        }

        function getCardUI(card)
        {
            var el = document.createElement('div');
            var icon = '';
            if (card.Suit == 'Hearts')
            icon='&hearts;';
            else if (card.Suit == 'Spades')
            icon = '&spades;';
            else if (card.Suit == 'Diamonds')
            icon = '&diams;';
            else
            icon = '&clubs;';
            
            el.className = 'card';
            el.innerHTML = card.Value + '<br/>' + icon;
            return el;
        }

      
        function getPoints(player)
        {
            var points = 0;
            var ace = 0;
            for(var i = 0; i < players[player].Hand.length; i++)
            {
                points += players[player].Hand[i].Weight;
                if(players[player].Hand[i].Weight == 11)
                    ace++;
            }
            if(ace>0 && points>21)
                points-=10;
            players[player].Points = points;
            return points;
        }

        function updatePoints()
        {
            for (var i = 0 ; i < players.length; i++)
            {
                getPoints(i);
                document.getElementById('points_' + i).innerHTML = players[i].Points;
            }
        }

        function stay()
        {
            if (currentPlayer != players.length-1) 
            {
                document.getElementById('player_' + currentPlayer).classList.remove('active');
                currentPlayer += 1;
                document.getElementById('player_' + currentPlayer).classList.add('active');
            }

            else {
                end();
            }
            
        }

        function end()
        {
            var winner = -1;
            var score = 0;

            for(var i = 0; i < players.length; i++)
            {
                if (players[i].Points > score && players[i].Points < 22)
                {
                    winner = i;
                }

                score = players[i].Points;
            }
            if(winner==0)
                {
                     document.getElementById('status').innerHTML = 'Выиграл: Дилер ';
                }
            else
                {
            document.getElementById('status').innerHTML = 'Выиграл: Игрок ' ;
                }
            document.getElementById("status").style.display = "inline-block";    
            document.getElementById("STOP").disabled = true;
            document.getElementById("STOP1").disabled = true;
        }

        function check()
        {
            if (players[currentPlayer].Points > 21)
            {
                if(currentPlayer==0)
                    {
                document.getElementById('status').innerHTML = 'Дилер проиграл';
                    }
                else
                    {
                     document.getElementById('status').innerHTML = 'Игрок проиграл';   
                    }
                document.getElementById('status').style.display = "inline-block";
                document.getElementById("STOP").disabled = true;
                document.getElementById("STOP1").disabled = true;
                end();
            }
            else if(players[currentPlayer].Points == 21)
            {
                end();
            }
        }

        function updateDeck()
        {
            document.getElementById('deckcount').innerHTML = deck.length;
        }
