function out = rdm_solve(x1, y1, x2, y2, x3, y3, dt12, dt13)
    syms xs ys
    c = 299792458;
    R12 = sqrt((xs-x1)^2+(ys-y1)^2)-sqrt((xs-x2)^2+(ys-y2)^2)==c*dt12/1000000;
    R13 = sqrt((xs-x1)^2+(ys-y1)^2)-sqrt((xs-x3)^2+(ys-y3)^2)==c*dt13/1000000;
    solution = solve([R12, R13], [xs, ys]);
    out = [double(solution.xs), double(solution.ys)];
    
    minX = min([x1,x2,x3]);
    maxX = max([x1,x2,x3]);
    minY = min([y1,y2,y3]);
    maxY = max([y1,y2,y3]);
    
    minX = minX(1)-(minX(1)+maxX(1))/5;
    maxX = maxX(1)+(minX(1)+maxX(1))/5;
    minY = minY(1)-(minY(1)+maxY(1))/5;
    maxY = maxY(1)+(minY(1)+maxY(1))/5;
    
    f1 = @(x,y) sqrt((x-x1)^2+(y-y1)^2)-sqrt((x-x2)^2+(y-y2)^2)-c*dt12/1000000;
    fimplicit(f1, [minX(1) maxX(1) minY(1) maxY(1)]);
    hold on
    f2 = @(x,y) sqrt((x-x1)^2+(y-y1)^2)-sqrt((x-x3)^2+(y-y3)^2)-c*dt13/1000000;
    fimplicit(f2, [minX(1) maxX(1) minY(1) maxY(1)]);
    
    plot(solution.xs, solution.ys, 'black*');
    plot(x1, y1, 'black*');
    plot(x2, y2, 'b*');
    plot(x3, y3, 'r*');
    hold off
end