import math

def draw_3d_capsule(width=80, height=40):
    # Набор символов для имитации освещения (от тени к свету)
    chars = " .:-=+*#%@"
    
    # Направление света (x, y, z)
    light_dir = [0.5, -0.5, -1.0]
    # Нормализация вектора света
    mag = math.sqrt(sum(i**2 for i in light_dir))
    light_dir = [i/mag for i in light_dir]

    for y in range(height):
        line = ""
        for x in range(width):
            # Преобразуем координаты в диапазон от -1 до 1
            nx = (x / width) * 2 - 1
            ny = (y / height) * 2 - 1
            ny *= (height / width) * 1.5 # Коррекция аспектного соотношения

            # Параметры формы (капсула)
            # z^2 = r^2 - x^2 - y^2 (упрощенно для сферы/цилиндра)
            radius = 0.4
            dist_sq = nx**2 + (max(0, abs(ny) - 0.5))**2
            
            if dist_sq < radius**2:
                # Вычисляем глубину Z
                nz = math.sqrt(radius**2 - dist_sq)
                
                # Вычисляем нормаль поверхности в этой точке
                # Для капсулы это будет примерно:
                normal = [nx/radius, (ny - (0.5 if ny > 0.5 else -0.5 if ny < -0.5 else ny))/radius, nz/radius]
                
                # Скалярное произведение (освещенность)
                diffuse = sum(normal[i] * -light_dir[i] for i in range(3))
                diffuse = max(0, diffuse)
                
                # Выбираем символ в зависимости от яркости
                char_idx = int(diffuse * (len(chars) - 1))
                line += chars[char_idx]
            else:
                line += " "
        print(line)

if __name__ == "__main__":
    draw_3d_capsule()