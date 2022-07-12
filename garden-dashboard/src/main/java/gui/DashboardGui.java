package gui;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;
import javax.swing.border.EmptyBorder;
import java.awt.BorderLayout;
import java.awt.GridLayout;

public class DashboardGui extends JFrame {
    private static final int WIDTH = 500;
    private static final int HEIGHT = 500;
    private static final String PROGRAM_TITLE = "Smart Garden - Dashboard";

    private final JLabel lblIntensity;
    private final JLabel lblTemperature;
    private final JLabel lblState;

    public DashboardGui() {
        GuiFactory guiFactory = new GuiFactory();

        // header with title
        JPanel titlePanel = new JPanel();
        JLabel lblProgramName = guiFactory.createTitle(PROGRAM_TITLE);
        titlePanel.add(lblProgramName);

        // central content with labels
        JPanel labelsPanel = new JPanel(new GridLayout(3, 3));
        labelsPanel.setBorder(new EmptyBorder(0, 80, 0, 80));
        lblIntensity = new JLabel();
        lblTemperature = new JLabel();
        lblState = new JLabel();

        labelsPanel.add(lblIntensity);
        labelsPanel.add(lblTemperature);
        labelsPanel.add(lblState);


        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setSize(WIDTH, HEIGHT);
        this.setTitle(PROGRAM_TITLE);

        this.add(titlePanel, BorderLayout.NORTH);
        this.add(labelsPanel, BorderLayout.CENTER);

        // center window on run
        this.setLocationRelativeTo(null);
        this.setVisible(true);
    }

    public void setIntensity(int intensity) {
        SwingUtilities.invokeLater(() -> lblIntensity.setText("Intensity: " + intensity));
    }

    public void setTemperature(int temperature) {
        SwingUtilities.invokeLater(() -> lblTemperature.setText("Temperature: " + temperature));
    }


    public void setState(String state) {
        SwingUtilities.invokeLater(() -> lblState.setText("state: " + state));
    }
}
