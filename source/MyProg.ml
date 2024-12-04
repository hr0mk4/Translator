program

record pair
begin
    x, y : int
end;

var 
    a, b : int,
    c, d2 : pair;
begin
    a:= 3;
    b:= a + 2;
    while (b >= a) do begin
        if (a = b) then begin
            write(100);
        end; else begin
            write(3);
        end;
        read(a);
        write(a);
    end;
    c.x := (a + 4);
    c.y := c.x * 100;
    d2 := c;
    write(d2.x);
    write(d2.y);
end