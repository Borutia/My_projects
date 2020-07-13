/*eslint-env browser*/


    var str = new Array();

    function func()
    {
        var temp;
        do
        {
            temp = prompt();
            if(temp != '')
            {
                str.push(temp)
            }
        }while(temp!='');
       //document.getElementById("mas_str").value;
            for(var i=0;i<str.length;i++)
                {
                    str[i] = str[i].replace(/[^a-z]/g, ' ');
                }
             alert(str);
    }