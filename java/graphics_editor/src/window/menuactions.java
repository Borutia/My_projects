package window;
import core.*;
import javax.swing.*;
import java.awt.event.ActionEvent;

public class menuactions {
    public menuactions(JPanel list, JMenu menu, JFrame win){
        Action loadimg = new AbstractAction("Загрузить") {
            @Override
            public void actionPerformed(ActionEvent e) {
            loadimage load = new loadimage();
            start.imag=load.load(list, win);
            start.loading = true;
            }
        };
        JMenuItem loadMenu = new JMenuItem(loadimg);
        menu.add(loadMenu);

        Action save = new AbstractAction("Сохранить") {
            @Override
            public void actionPerformed(ActionEvent e) {
            save saveimg = new save();
            saveimg.saveimg(win);
            }
        };
        JMenuItem saveMenu = new JMenuItem(save);
        menu.add(saveMenu);

        Action saveas = new AbstractAction("Сохранить как") {
            @Override
            public void actionPerformed(ActionEvent e) {
                save sv = new save();
                sv.saveimg(win);
            }
        };
        JMenuItem saveasMenu = new JMenuItem(saveas);
        menu.add(saveasMenu);
    }
}
