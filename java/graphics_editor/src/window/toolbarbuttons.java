package window;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class toolbarbuttons {
    public toolbarbuttons(JToolBar toolBar, start rez){
        JButton penbutton = new JButton(new ImageIcon("pen.png"));
        penbutton.setBounds(10,40,50,50);
        penbutton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                rez.getrez(0);
            }
        });
        toolBar.add(penbutton);

        JButton brushbutton = new JButton(new ImageIcon(("brush.png")));
        brushbutton.setBounds(70,40,50,50);
        brushbutton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                rez.getrez(1);
            }
        });
        toolBar.add(brushbutton);

        JButton lasticbutton = new JButton(new ImageIcon("lastik.png"));
        lasticbutton.setBounds(130,40,50,50);
        lasticbutton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                rez.getrez(2);
            }
        });
        toolBar.add(lasticbutton);

        JButton text = new JButton(new ImageIcon("text.png"));
        text.setBounds(10,100,50,50);
        text.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                rez.getrez(3);
            }
        });
        toolBar.add(text);

        JButton linebutton = new JButton(new ImageIcon("line.png"));
        linebutton.setBounds(10,190,50,50);
        linebutton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                rez.getrez(4);
            }
        });
        toolBar.add(linebutton);

        JButton ovalbutton = new JButton(new ImageIcon("oval.png"));
        ovalbutton.setBounds(70,190,50,50);
        ovalbutton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                rez.getrez(5);
            }
        });
        toolBar.add(ovalbutton);

        JButton quadbutton = new JButton(new ImageIcon("rect.png"));
        quadbutton.setBounds(130,190,50,50);
        quadbutton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                rez.getrez(6);
            }
        });
        toolBar.add(quadbutton);
        toolBar.setLayout(null);
    }
}
