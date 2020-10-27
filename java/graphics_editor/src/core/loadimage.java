package core;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.image.*;
import java.io.*;

public class loadimage {
    private static BufferedImage imag;
    boolean loading = false;
    private String filename;

    public BufferedImage getImag(){
        return imag;
    }

    public void setImag(BufferedImage img){
        this.imag = img;
    }

    public BufferedImage load(JPanel list, JFrame win){
        JFileChooser file = new JFileChooser();
        int result = file.showOpenDialog(null);
        if(result==JFileChooser.APPROVE_OPTION){
            try{
                filename = file.getSelectedFile().getAbsolutePath();
                File inputfile = new File(filename);
                file.addChoosableFileFilter(new TextFileFilter(".png"));
                file.addChoosableFileFilter(new TextFileFilter(".jpg"));
                imag = ImageIO.read(inputfile);
                loading = true;
                win.setSize(imag.getWidth()+40, imag.getWidth()+80);
                list.setSize(imag.getWidth(), imag.getWidth());
                list.repaint();
                return imag;
                }catch (FileNotFoundException e){
                JOptionPane.showMessageDialog(win, "Такого файла не существует");
                return imag;
            }
                catch (IOException e) {
                JOptionPane.showMessageDialog(win, "Исключение ввода-вывода");
                return imag;
            }
        }
        return  imag;
    }
}
