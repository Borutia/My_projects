package window;
import core.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class colorsbuttons {  // сами кнопки
    public colorsbuttons(JToolBar colorbar, mcolor color){
        JButton colorbutton = new JButton();
        colorbutton.setBackground(color.getMaincolor());
        colorbutton.setBounds(15,15,30,30);
        colorbar.add(colorbutton);

        JButton redbut = new JButton();
        redbut.setBackground(Color.red);
        redbut.setBounds(55,20,20,20);
        redbut.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                color.setMaincolor(Color.red);
                colorbutton.setBackground(color.getMaincolor());
            }
        });
        colorbar.add(redbut);

        JButton orbut = new JButton();
        orbut.setBackground(Color.orange);
        orbut.setBounds(85,20,20,20);
        orbut.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                color.setMaincolor(Color.orange);
                colorbutton.setBackground(color.getMaincolor());
            }
        });
        colorbar.add(orbut);

        JButton yebut = new JButton();
        yebut.setBackground(Color.yellow);
        yebut.setBounds(115,20,20,20);
        yebut.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                color.setMaincolor(Color.yellow);
                colorbutton.setBackground(color.getMaincolor());
            }
        });
        colorbar.add(yebut);

        JButton blbut = new JButton();
        blbut.setBackground(Color.blue);
        blbut.setBounds(145,20,20,20);
        blbut.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                color.setMaincolor(Color.blue);
                colorbutton.setBackground(color.getMaincolor());
            }
        });
        colorbar.add(blbut);

        JButton cybut = new JButton();
        cybut.setBackground(Color.cyan);
        cybut.setBounds(175,20,20,20);
        cybut.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                color.setMaincolor(Color.cyan);
                colorbutton.setBackground(color.getMaincolor());
            }
        });
        colorbar.add(cybut);

        JButton grbut = new JButton();
        grbut.setBackground(Color.green);
        grbut.setBounds(205,20,20,20);
        grbut.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                color.setMaincolor(Color.green);
                colorbutton.setBackground(color.getMaincolor());
            }
        });
        colorbar.add(grbut);

        JButton bbut = new JButton();
        bbut.setBackground(Color.black);
        bbut.setBounds(235,20,20,20);
        bbut.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                color.setMaincolor(Color.black);
                colorbutton.setBackground(color.getMaincolor());
            }
        });
        colorbar.add(bbut);

        colorbar.setLayout(null);
    }
}
