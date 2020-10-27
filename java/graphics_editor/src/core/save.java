package core;

import window.start;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import static window.start.imag;

public class save {
    private String filename;
    public void saveimg(JFrame win){
        try {
            JFileChooser file = new JFileChooser();
            TextFileFilter pngFilter = new TextFileFilter(".png");
            TextFileFilter jpgFilter = new TextFileFilter(".jpg");
            if (filename == null) {
                file.addChoosableFileFilter(pngFilter);
                file.addChoosableFileFilter(jpgFilter);
                int result = file.showSaveDialog(null);
                if (result == JFileChooser.APPROVE_OPTION) {
                    filename = file.getSelectedFile().getAbsolutePath();
                }
            }
            if (file.getFileFilter() == pngFilter) {
                ImageIO.write(start.imag, "png", new File(filename + ".png"));
            } else {
                ImageIO.write(start.imag, "jpeg", new File(filename + ".jpg"));
            }
        }catch (IOException e){
            JOptionPane.showMessageDialog(win, "Ошибка ввода-вывода");
        }
    }
}
