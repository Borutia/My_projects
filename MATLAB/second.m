x = input('x = ');
a = -10;
b = 17;
h = 0.6;



ezplot('sin((x/2)+7)+3',[a,b]);
hold on


while a < b
    y1 = func_one(x);
    y2 = func_two(x);
    
    a = a + h;
end


function f = func_one(x)
f = sin((x/2)+7)+3;
end

function f = func_two(x)
f = sqrt(abs(x+6));
end

        