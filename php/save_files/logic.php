<?php
    // путь куда сохраняем файл
    $path = 'C:\xampp\htdocs\php\i\\';
    // проверка, что файл отправлен
    if (!empty($_FILES['image']['name'])) 
    {
        $file_name = $_FILES['image']['name'];
        // получаем расширение файла
        $filetype1 = explode('.', $file_name);
        $filetype = $filetype1[count($filetype1)-1];
        // проверяем расширение файла
        if ($filetype == "bmp" || $filetype == "gif" || $filetype == "jpg" || $filetype == "jpeg")
        {
            // сохраняем файл по пути
            if (!@copy($_FILES['image']['tmp_name'], $path . $_FILES['image']['name']))
            {
                echo 'Что-то пошло не так';
            }
            else
            {
                // вывод картинки на страницу
                echo "<img src='", $path, $_FILES['image']['name'], "'>";
            }
        }
        else // если файл не с расширекм как надо 
        {
            if (!@copy($_FILES['image']['tmp_name'], $path . $_FILES['image']['name']))
            {
                echo 'Что-то пошло не так';
            }
            else
            {
                echo "Файл получен и записан по адресу: ", $path, $_FILES['image']['name'];
            }
        }
    } 
    else 
    {
        echo "Файл не выбран!";
    }
    echo "<p><a href='index.html'>Вернуться на главную</a></p>"
?>