package gui;

import javax.swing.JButton;
import javax.swing.JLabel;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;

/**
 * Factory pattern to create UI elements with custom style easily.
 */
public class GuiFactory {

    public JLabel createTitle(String text) {
        JLabel lblTitle = new JLabel(text);
        Font boldFont = new Font(lblTitle.getFont().getName(), Font.BOLD, 30);
        lblTitle.setFont(boldFont);

        return lblTitle;
    }

    public JButton createPrimaryButton(String text) {
        JButton primaryButton = new JButton(text);
        primaryButton.setBackground(Color.decode("#7d8cff"));
        primaryButton.setForeground(Color.BLACK);
        primaryButton.setPreferredSize(new Dimension(150, 40));

        return primaryButton;
    }

}
