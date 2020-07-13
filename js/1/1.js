/*eslint-env browser*/

    function func()
    {
        var arr = new Array();
        var temp;
        var test = 0;
        var n = document.getElementById("count").value;
        for(var i=0;i<n;i++)
            {
                 test = 0;
                 temp = Math.floor(Math.random() * 20);
                 for(var j=0;j<arr.length;j++)
                     {
                         if(arr[j]==temp)
                             {
                                 test++;
                             }
                     }
                 if(test==0)
                     {
                         arr.push(temp);
                     }
                 else 
                    {
                        i--;
                    }
            }
        alert(arr);
    }