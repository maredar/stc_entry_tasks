function ITD_stereo_sound_gen(source_linear_speed, source_distance_radius)
    R = source_distance_radius/100;    
    w = source_linear_speed/R;
    ear_distance = 20.4/100;
    v_sound = 340.29;
    
    %параметры для audiowrite
    F_sample = 44000;
    dt = 1/F_sample;
    t = 0:dt:20;
    %начальные параметры сигнала
    phi = 0;
    F = 200;
    A = 1;
    
    x_source = R * cos(w*t);
    y_source = R * sin(w*t);
    
    y_l = 0; y_r = 0;
    x_l = -ear_distance/2;
    x_r = ear_distance/2;
    %расстояние от источника до левого и правого уха соответственно
    dist_left = sqrt((x_source-x_l).^2+(y_source-y_l).^2);
    dist_right = sqrt((x_source-x_r).^2+(y_source-y_r).^2);
    %время получения звука левым и правым ушами
    dt_left = dist_left/v_sound;
    dt_right = dist_right/v_sound;
    
    sound_left = A*sin((2*pi*F*(t+dt_left))+phi);
    sound_right = A*sin((2*pi*F*(t+dt_right))+phi);
    
    stereo_sound = [sound_left(:), sound_right(:)];
    audiowrite('stereo sound.wav', stereo_sound, F_sample);
end