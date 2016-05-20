program test;

begin
    var a, b, c: integer;
    a := 10;
    b := 20.0;

    if (a < b) then
        c := b;
        b := a;
        a := c;
    else if (a = b) then
        c := a + b;
    else
        c := 100;
end.
