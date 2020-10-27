package window;

import javax.swing.*;

public class menubar {
    public menubar(JPanel list, JFrame win){
        JMenuBar menuBar = new JMenuBar();
        win.setJMenuBar(menuBar);
        menuBar.setBounds(0,0,350,30);
        JMenu fileMenu = new JMenu("Файл");
        menuBar.add(fileMenu);
        menuactions menu = new menuactions(list, fileMenu, win);
    }
}
