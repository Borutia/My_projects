function count=prime(n,m)
a=uint16(n);
b=uint16(m);

count=0;

if (a<=2)
    disp(2);
    count=1;
end

while (a<=b)
    for i=2:(a-1)
        if (mod(a,i)==0)
            break;
        elseif (i==(a-1))
            disp(a);
            count=count+1;
        end
    end
    a=a+1;    
end




    