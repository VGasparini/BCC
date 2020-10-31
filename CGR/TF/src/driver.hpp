#ifndef __RT_MENU__
#define __RT_MENU__

void consoleReader(sf::RenderWindow *window)
{
    double f_x, f_y, f_z, f_a, f_b, f_c;
    int i_a, i_b;

    std::string line, op;
    std::stringstream command;
    while (window->isOpen())
    {
        rmut.lock();
        // Start interpreter
        printf("> ");
        std::getline(std::cin, line);
        command = std::stringstream(line);
        std::cout << "Command: " << command.str() << std::endl;
        command >> op;
        ToLowerString(op);
        if (op == "set")
        {
            command >> op;
            if (op == "campos")
            {
                command >> f_x >> f_y >> f_z;
                campos.Set(f_x, f_y, f_z);
            }
            else if (op == "camangle")
            {
                command >> f_x >> f_y >> f_z;
                camlook.Set(f_x, f_y, f_z);
            }
            else if (op == "zoom")
            {
                command >> f_a;
                zoom = f_a;
            }
            else if (op == "contrast")
            {
                command >> f_a;
                contrast = f_a;
            }
            else if (op == "depth")
            {
                command >> i_a;
                if (i_a < 1)
                    i_a = 1;
                MAXTRACE = unsigned(i_a);
            }
            else if (op == "res")
            {
                command >> i_a >> i_b;
                dmut.lock();
                rW = unsigned(i_a);
                rH = unsigned(i_b);
                delete pixels;
                pixels = new sf::Uint8[rW * rH * 4];
                if (!texture.create(rW, rH))
                {
                    printf("Error on texture resizing!\n");
                    break;
                }
                sprite.setTexture(texture, true);
                float sX = W / float(rW), sY = H / float(rH);
                printf("Nova escala: x=%f, y=%f\n", sX, sY);
                sprite.setScale(sX, sY);
                dmut.unlock();
            }
            else if (op == "scale")
            {
                command >> f_a;
                dmut.lock();
                rW = unsigned(W * f_a);
                rH = unsigned(H * f_a);
                delete pixels;
                pixels = new sf::Uint8[rW * rH * 4];
                if (!texture.create(rW, rH))
                {
                    printf("Error on texture resizing!\n");
                    break;
                }
                texture.setSmooth(f_a > 1);
                sprite.setTexture(texture, true);
                float sX = W / float(rW), sY = H / float(rH);
                printf("Nova escala: x=%f, y=%f\n", sX, sY);
                sprite.setScale(sX, sY);
                dmut.unlock();
            }
            else if (op == "shadowres")
            {
                command >> i_a;
                if (i_a < 1)
                    i_a = 1;
                SHADOW_RES = i_a;
                InitArealightVectors();
            }
            else if (op == "scatter")
            {
                command >> i_a;
                if (i_a < 1)
                    i_a = 1;
                SURFACE_SAMPLES = i_a;
            }
            else if (op == "lightfall")
            {
                command >> f_a;
                LIGHT_FALLOFF = f_a;
            }
            else if (op == "sphere")
            {
                command >> i_a >> op;
                if (i_a < 0 || i_a >= Spheres.size())
                    continue;
                if (op == "move")
                {
                    command >> f_x >> f_y >> f_z;
                    Spheres[i_a].center += XYZ{{f_x, f_y, f_z}};
                }
                else if (op == "pos")
                {
                    command >> f_x >> f_y >> f_z;
                    Spheres[i_a].center.Set(f_x, f_y, f_z);
                }
                else if (op == "color")
                {
                    command >> f_a >> f_b >> f_c;
                    Spheres[i_a].mtl.color.Set(f_a, f_b, f_c);
                }
                else if (op == "radius")
                {
                    command >> f_a;
                    Spheres[i_a].radius = f_a;
                }
                else if (op == "rough")
                {
                    command >> f_a;
                    Spheres[i_a].mtl.roughness = f_a;
                }
                else if (op == "shiny")
                {
                    command >> f_a;
                    Spheres[i_a].mtl.shininess = f_a;
                }
                else if (op == "refindex")
                {
                    command >> f_a;
                    Spheres[i_a].mtl.refraction = f_a;
                }
            }
            else if (op == "plane")
            {
                command >> i_a >> op;
                if (i_a < 0 || i_a >= Planes.size())
                    continue;
                if (op == "normal")
                {
                    command >> f_x >> f_y >> f_z;
                    Planes[i_a].normal.Set(f_x, f_y, f_z);
                    Planes[i_a].normal.Normalize();
                }
                else if (op == "color")
                {
                    command >> f_a >> f_b >> f_c;
                    Planes[i_a].mtl.color.Set(f_a, f_b, f_c);
                }
                else if (op == "offset")
                {
                    command >> f_a;
                    Planes[i_a].offset = f_a;
                }
                else if (op == "rough")
                {
                    command >> f_a;
                    Planes[i_a].mtl.roughness = f_a;
                }
                else if (op == "shiny")
                {
                    command >> f_a;
                    Planes[i_a].mtl.shininess = f_a;
                }
            }
        }
        else if (op == "add")
        {
            command >> op >> f_x >> f_y >> f_z;
            if (op == "sphere")
            {
                command >> f_a >> f_b; // Read radius and roughness
                Spheres.push_back({{f_x, f_y, f_z}, f_a, f_b});
            }
            else if (op == "light")
            {
                command >> f_a >> f_b >> f_c; // Read color
                Lights.push_back({{f_x, f_y, f_z}, {f_a, f_b, f_c}});
            }
            else if (op == "plane")
            {
                command >> f_a; // Read distance
                XYZ dir{{f_x, f_y, f_z}};
                dir.Normalize();
                Planes.push_back({dir, f_a});
            }
        }
        else if (op == "list")
        {
            command >> op;
            if (op == "sphere")
            {
                printf("Spheres:\n id |   x  |   y  |   z  |radius|  r |  g |  b |rough|shiny\n");
                for (int i = 0; i < Spheres.size(); i++)
                {
                    XYZ pos = Spheres[i].center;
                    double rad = Spheres[i].radius;
                    Material *mtl = &Spheres[i].mtl;
                    printf("%3d |%6.2f|%6.2f|%6.2f|%6.2f|"
                           "%4.2f|%4.2f|%4.2f|%5.3f|%5.3f\n",
                           i, pos[0], pos[1], pos[2], rad,
                           mtl->color[0], mtl->color[1], mtl->color[2],
                           mtl->roughness, mtl->shininess);
                }
            }
            if (op == "light")
            {
                printf("Lights:\n id |   x  |   y  |   z  |  r  |  g  |  b\n");
                for (int i = 0; i < Lights.size(); i++)
                {
                    XYZ pos = Lights[i].center;
                    XYZ rgb = Lights[i].colour;
                    printf("%3d |%6.2f|%6.2f|%6.2f|%5.2f|%5.2f|%5.2f\n",
                           i, pos[0], pos[1], pos[2], rgb[0], rgb[1], rgb[2]);
                }
            }
            if (op == "plane")
            {
                printf("Planes:\n id |   x  |   y  |   z  |offset|  r |  g |  b |rough|shiny\n");
                for (int i = 0; i < Planes.size(); i++)
                {
                    XYZ pos = Planes[i].normal;
                    double offset = Planes[i].offset;
                    Material *mtl = &Planes[i].mtl;
                    printf("%3d |%6.2f|%6.2f|%6.2f|%6.2f|"
                           "%4.2f|%4.2f|%4.2f|%5.3f|%5.3f\n",
                           i, pos[0], pos[1], pos[2], offset,
                           mtl->color[0], mtl->color[1], mtl->color[2],
                           mtl->roughness, mtl->shininess);
                }
            }
        }
        else if (op == "rem")
        {
            command >> op >> i_a;
            if (op == "sphere")
            {
                if (i_a >= 0 && i_a < Spheres.size())
                    Spheres.erase(Spheres.begin() + i_a);
            }
            else if (op == "light")
            {
                if (i_a >= 0 && i_a < Lights.size())
                    Lights.erase(Lights.begin() + i_a);
            }
            else if (op == "plane")
            {
                if (i_a >= 0 && i_a < Planes.size())
                    Planes.erase(Planes.begin() + i_a);
            }
        }
        else if (op == "resize")
        {
            command >> i_a >> i_b;
            W = unsigned(i_a);
            H = unsigned(i_b);
            float sX = W / float(rW), sY = H / float(rH);
            printf("Nova escala: x=%f, y=%f\n", sX, sY);
            resize = true;
            sprite.setScale(sX, sY);
            sprite.setTexture(texture, true);
        }
        else if (op == "render")
        {
            rerender = true;
        }
        if (op == "export")
        {
            command >> outfile;
            toFile = true;
        }
        else if (op == "exit")
        {
            die = true;
            break;
        }
        rmut.unlock();
        sleep(50);
    }
}

#endif
