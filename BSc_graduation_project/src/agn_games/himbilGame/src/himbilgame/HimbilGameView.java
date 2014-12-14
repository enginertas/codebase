/*
 * HimbilGameView.java
 */

package himbilgame;

import java.util.logging.Level;
import java.util.logging.Logger;
import org.jdesktop.application.Action;
import org.jdesktop.application.ResourceMap;
import org.jdesktop.application.SingleFrameApplication;
import org.jdesktop.application.FrameView;
import org.jdesktop.application.TaskMonitor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Calendar;
import java.util.GregorianCalendar;
import javax.swing.Timer;
import javax.swing.Icon;
import javax.swing.JDialog;
import javax.swing.JFrame;
import java.util.Random;
/**
 * The application's main frame.
 */
public class HimbilGameView extends FrameView {

    public HimbilGameView(SingleFrameApplication app)
    {
        super(app);

        initComponents();

        // status bar initialization - message timeout, idle icon and busy animation, etc
        ResourceMap resourceMap = getResourceMap();
        int messageTimeout = resourceMap.getInteger("StatusBar.messageTimeout");
        messageTimer = new Timer(messageTimeout, new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                statusMessageLabel.setText("");
            }
        });
        messageTimer.setRepeats(false);
        int busyAnimationRate = resourceMap.getInteger("StatusBar.busyAnimationRate");
        for (int i = 0; i < busyIcons.length; i++) {
            busyIcons[i] = resourceMap.getIcon("StatusBar.busyIcons[" + i + "]");
        }
        busyIconTimer = new Timer(busyAnimationRate, new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                busyIconIndex = (busyIconIndex + 1) % busyIcons.length;
                statusAnimationLabel.setIcon(busyIcons[busyIconIndex]);
            }
        });
        idleIcon = resourceMap.getIcon("StatusBar.idleIcon");
        statusAnimationLabel.setIcon(idleIcon);
        progressBar.setVisible(false);

        // connecting action tasks to status bar via TaskMonitor
        TaskMonitor taskMonitor = new TaskMonitor(getApplication().getContext());
        taskMonitor.addPropertyChangeListener(new java.beans.PropertyChangeListener() {
            public void propertyChange(java.beans.PropertyChangeEvent evt) {
                String propertyName = evt.getPropertyName();
                if ("started".equals(propertyName)) {
                    if (!busyIconTimer.isRunning()) {
                        statusAnimationLabel.setIcon(busyIcons[0]);
                        busyIconIndex = 0;
                        busyIconTimer.start();
                    }
                    progressBar.setVisible(true);
                    progressBar.setIndeterminate(true);
                } else if ("done".equals(propertyName)) {
                    busyIconTimer.stop();
                    statusAnimationLabel.setIcon(idleIcon);
                    progressBar.setVisible(false);
                    progressBar.setValue(0);
                } else if ("message".equals(propertyName)) {
                    String text = (String)(evt.getNewValue());
                    statusMessageLabel.setText((text == null) ? "" : text);
                    messageTimer.restart();
                } else if ("progress".equals(propertyName)) {
                    int value = (Integer)(evt.getNewValue());
                    progressBar.setVisible(true);
                    progressBar.setIndeterminate(false);
                    progressBar.setValue(value);
                }
            }
        });
        // start of code //
        panelCentral.setVisible(false);
        butPass.setEnabled(false);
        txtPass.setEnabled(false);
        menuBar.setVisible(false);
//        statusBar.setBorder(0, 0, 0 ,0 );
        startGame();
    }
    private int[] mixCards(int[] possible, int size)
    {
        Calendar cal = new GregorianCalendar();
        Random generator = new Random(cal.getTimeInMillis());
        int i, j, k, pivot;
        for(i = 0; i < 2000; i++)
        {
            int inter[] = new int[size];
            pivot = generator.nextInt(size);
            for (j = 0; j < size; j++)
                inter[j] = possible[(j + pivot) % size];
            
            for (j = 0; j < size; j++)
                possible[j] = inter[j];

            pivot = generator.nextInt(4);
            for (j = 0; j < 4; j++)
                inter[j] = possible[(j + pivot + 1) % 4];
            
            for (j = 0; j < size; j++)
                possible[j] = inter[j];
        }
        return possible;
    }
    private void establishCards()
    {
        int i, j, poss_size, possible[];
        poss_size = player_count * 4;
        possible = new int[poss_size];
        
        for(i = 0; i < poss_size; i++)
            possible[i] = i % player_count + 1;
        possible = mixCards(possible, poss_size);

        user_cards = new int[player_count][4];
        for(i = 0; i < poss_size; i++)
            user_cards[i/4][i % 4] = possible[i];

        String[] to_send = new String[player_count + 1];
        to_send[0] = "cards " + player_count;
        for(i = 0; i < player_count; i++)
            to_send[i + 1] = user_cards[i][0] + " " + user_cards[i][1] + " "
                    + user_cards[i][2] + " " + user_cards[i][3];

        game_inter.sendMessage(to_send, player_count + 1);
    }
    private void placeCards(String[] card_places)
    {
        int i,j, size;
        user_cards = new int[player_count][4];
        String message[] = card_places[0].split(" ");
        
        if(message[0].equals("cards"))
        {
            size = Integer.decode(message[1]);
            for(i = 0; i < size; i++)
            {
                message = card_places[i + 1].split(" ");
                for(j = 0; j < 4; j++)
                   user_cards[i][j] = Integer.decode(message[j]);
            }
        }
        else
        {
            game_inter.rejectGame("Game is terminated because of messages that are out-of-standard");
            System.exit(0);
        }
    }
    private void organizePanels()
    {
        int i;
        user_panels = new javax.swing.JLabel[player_count];
        for(i = 0; i < player_count; i++)
        {
              user_panels[i] = new javax.swing.JLabel();
              user_panels[i].setBackground(panelCentral.getBackground());
              user_panels[i].setForeground(panelCentral.getForeground());
              user_panels[i].setFont(panelCentral.getFont());
              user_panels[i].setHorizontalAlignment(panelCentral.getHorizontalAlignment());
              user_panels[i].setName("panel" + i);
              //user_panels[i].setBorder(panelCentral.getBorder());

              user_panels[i].setText("");
        }

        user_panels[0].setBounds(190, 250, 71, 31);
        user_panels[1].setBounds(20, 125, 71, 71);
        mainPanel.add(user_panels[0], user_panels[0].getName());
        mainPanel.add(user_panels[1], user_panels[1].getName());
        
        switch(player_count)
        {
            case 2:
                switch(player_id)
                {
                    case 0:
                        user_panels[1].setIcon(panelCentral.getDisabledIcon());
                        break;
                    case 1:
                        user_panels[0].setIcon(panelCentral.getDisabledIcon());
                        break;
                }
                break;
            case 3:
                user_panels[2].setBounds(190, 20, 71, 31);
                mainPanel.add(user_panels[2], user_panels[2].getName());
                switch(player_id)
                {
                    case 0:
                        user_panels[2].setIcon(panelCentral.getDisabledIcon());
                        user_panels[1].setIcon(panelCentral.getDisabledIcon());
                        break;
                    case 1:
                        user_panels[0].setIcon(panelCentral.getDisabledIcon());
                        user_panels[2].setIcon(panelCentral.getDisabledIcon());
                        break;
                    case 2:
                        user_panels[0].setIcon(panelCentral.getDisabledIcon());
                        user_panels[1].setIcon(panelCentral.getDisabledIcon());
                        break;
                }
                break;
            case 4:
                user_panels[2].setBounds(190, 20, 71, 31);
                user_panels[3].setBounds(360, 145, 71, 31);
                mainPanel.add(user_panels[2], user_panels[2].getName());
                mainPanel.add(user_panels[3], user_panels[3].getName());
                switch(player_id)
                {
                    case 0:
                        user_panels[3].setIcon(panelCentral.getDisabledIcon());
                        user_panels[2].setIcon(panelCentral.getDisabledIcon());
                        user_panels[1].setIcon(panelCentral.getDisabledIcon());
                        break;
                    case 1:
                        user_panels[0].setIcon(panelCentral.getDisabledIcon());
                        user_panels[2].setIcon(panelCentral.getDisabledIcon());
                        user_panels[3].setIcon(panelCentral.getDisabledIcon());
                        break;
                    case 2:
                        user_panels[0].setIcon(panelCentral.getDisabledIcon());
                        user_panels[1].setIcon(panelCentral.getDisabledIcon());
                        user_panels[3].setIcon(panelCentral.getDisabledIcon());
                        break;
                    case 3:
                        user_panels[0].setIcon(panelCentral.getDisabledIcon());
                        user_panels[1].setIcon(panelCentral.getDisabledIcon());
                        user_panels[2].setIcon(panelCentral.getDisabledIcon());
                        break;
                }
                break;
        }
    }
    private void setCards()
    {
        int i;
        javax.swing.JLabel my_panel = user_panels[player_id];
        my_panel.setText("");
        if(player_id == 0)
        {
            if(recent_card == -1)
            {
                for(i = 0; i < 4; i++)
                    if(user_cards[0][i] != -1)
                        my_panel.setText(my_panel.getText() + user_cards[0][i] + " ");
            }
            else
            {
                for(i = 0; i < 4; i++)
                {
                    if(user_cards[0][i] == -1)
                        user_cards[0][i] = recent_card;

                    my_panel.setText(my_panel.getText() + user_cards[0][i] + " ");
                    
                }
                recent_card = -1;
            }
        }
        else
        {
            if(recent_card == -1)
                for(i = 0; i < 4 ; i++)
                    my_panel.setText(my_panel.getText() + user_cards[player_id][i] + " ");
            else
            {
                my_panel.setText(recent_card + " ");
                for(i = 0; i < 4 ; i++)
                    my_panel.setText(my_panel.getText() + user_cards[player_id][i] + " ");
            }
        }
    }
    private boolean checkEndGame()
    {
        boolean result = true;
        int card = user_cards[player_id][0], i;
        for(i = 1; i < 4; i++)
            if(user_cards[player_id][i] != card)
                result = false;

        if(result)
        {
            String message;
            message = player_id + " " + card;
            game_inter.sendWinner(message);
            game_inter.rejectGame("The Game is Over. We congratulate YOU!");
            lblSituation.setText("Himbil! The winner is YOU");
            try {
                Thread.sleep(10000);
            } catch (InterruptedException ex) {
                Logger.getLogger(HimbilGameView.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        return result;
    }
    private void makeMove()
    {
        if(player_id == 0)
        {
            going_card = user_cards[0][gc_index];
            user_cards[0][gc_index] = -1;
        }
        else
        {
            if(gc_index == 'r')
                going_card = recent_card;
            else
            {
                going_card = user_cards[player_id][gc_index];
                user_cards[player_id][gc_index] = recent_card;
            }
        }
        is_move_made = false;
        gc_index = -1;
        recent_card = -1;       
        game_order = (game_order + 1) % player_count;
        lblSituation.setText("Order is at player " + game_order);
    }
    private void sendMove()
    {
        String messages[] = new String[1];
        messages[0] = "move " + player_id + " " + going_card;
        game_inter.sendMessage(messages, 1);
        going_card = -1;
    }

    @SuppressWarnings("empty-statement")
    private void cycleGame()
    {
        lblSituation.setText("Order is at player " + game_order);
        setCards();
        while(true)
        {         
            if(game_order == player_id)
            {
                setCards();
                txtPass.setEnabled(true);
                butPass.setEnabled(true);
                if(player_id == 0)
                {
                    if(checkEndGame())
                         break;
                    else
                    {
                        while(!is_move_made);
                        makeMove();
                        setCards();
                        sendMove();
                    }
                }
                else
                {
                    while(!is_move_made);
                    makeMove();
                    setCards();                 
                    if(checkEndGame())
                        break;
                    sendMove();
                }               
                txtPass.setEnabled(false);
                butPass.setEnabled(false);
            }
            else
            {
                String message[] = null, new_move[];
                int index;
                message = game_inter.getRemoteMessage();
                
                if(message != null)
                {
                    new_move = message[0].split(" ");
                    if(new_move[0].equals("move"))
                    {
                        index = Integer.decode(new_move[1]);
                        if(index == game_order)
                        {
                            if ((index + 1) % player_count == player_id)
                            {
                                //setCards();
                                recent_card = Integer.decode(new_move[2]);
                                setCards();
                            }
                            game_order = (game_order + 1) % player_count;
                            lblSituation.setText("Order is at Player " + game_order );
                        }
                    }
                    else if(new_move[0].equals("winner"))
                    {
                        index = Integer.decode(new_move[1]);
                        game_inter.rejectGame("The Game is Over. We congratulate Player " + index + "!");
                        lblSituation.setText("Himbil! The winner is Player " + index);
                        user_panels[index].setText(new_move[2] + " " + new_move[2] + " " + new_move[2] + " " + new_move[2]);
                        user_panels[index].setIcon(null);
                        try {
                            Thread.sleep(10000);
                        } catch (InterruptedException ex) {
                            Logger.getLogger(HimbilGameView.class.getName()).log(Level.SEVERE, null, ex);
                        }
                        break;
                    }
                }
            }
        }
    }
    private void startGame()
    {
        // get number of players, if suitable continue
        player_count = game_inter.getPlayerCount();
        if(player_count < 2 || player_count > 4)
        {
            game_inter.rejectGame("Illegal number of players to play: " + player_count);
            System.exit(1);
        }
        // accept and get the order of player
        player_id = game_inter.getPlayerOrder();
        if(player_id == -1)
        {
            game_inter.rejectGame("Connection Error");
            System.exit(1);
        }

        // organize user panels
        organizePanels();
        // if player is server, establish cards; else wait card order and adjust them
        if(player_id == 0)
            establishCards();
        else
        {
            String[]  messages = game_inter.getRemoteMessage();
            placeCards(messages);
        }
        //then cycle the game

        Runnable r = new Runnable(){public void run(){ cycleGame(); }};
        Thread th = new Thread(r);
        th.start();
        //System.exit(0);
    }
    
    @Action
    public void showAboutBox() {
        if (aboutBox == null) {
            JFrame mainFrame = HimbilGameApp.getApplication().getMainFrame();
            aboutBox = new HimbilGameAboutBox(mainFrame);
            aboutBox.setLocationRelativeTo(mainFrame);
        }
        HimbilGameApp.getApplication().show(aboutBox);
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        mainPanel = new javax.swing.JPanel();
        txtPass = new javax.swing.JTextField();
        butPass = new javax.swing.JButton();
        jLabel1 = new javax.swing.JLabel();
        panelCentral = new javax.swing.JLabel();
        lblSituation = new javax.swing.JLabel();
        menuBar = new javax.swing.JMenuBar();
        javax.swing.JMenu fileMenu = new javax.swing.JMenu();
        javax.swing.JMenuItem exitMenuItem = new javax.swing.JMenuItem();
        javax.swing.JMenu helpMenu = new javax.swing.JMenu();
        javax.swing.JMenuItem aboutMenuItem = new javax.swing.JMenuItem();
        statusPanel = new javax.swing.JPanel();
        javax.swing.JSeparator statusPanelSeparator = new javax.swing.JSeparator();
        statusMessageLabel = new javax.swing.JLabel();
        statusAnimationLabel = new javax.swing.JLabel();
        progressBar = new javax.swing.JProgressBar();

        mainPanel.setMaximumSize(new java.awt.Dimension(449, 317));
        mainPanel.setMinimumSize(new java.awt.Dimension(449, 317));
        mainPanel.setName("mainPanel"); // NOI18N
        mainPanel.setPreferredSize(new java.awt.Dimension(449, 317));

        org.jdesktop.application.ResourceMap resourceMap = org.jdesktop.application.Application.getInstance(himbilgame.HimbilGameApp.class).getContext().getResourceMap(HimbilGameView.class);
        txtPass.setText(resourceMap.getString("txtPass.text")); // NOI18N
        txtPass.setName("txtPass"); // NOI18N

        javax.swing.ActionMap actionMap = org.jdesktop.application.Application.getInstance(himbilgame.HimbilGameApp.class).getContext().getActionMap(HimbilGameView.class, this);
        butPass.setAction(actionMap.get("Click")); // NOI18N
        butPass.setFont(resourceMap.getFont("butPass.font")); // NOI18N
        butPass.setText(resourceMap.getString("butPass.text")); // NOI18N
        butPass.setName("butPass"); // NOI18N

        jLabel1.setFont(resourceMap.getFont("jLabel1.font")); // NOI18N
        jLabel1.setText(resourceMap.getString("jLabel1.text")); // NOI18N
        jLabel1.setName("jLabel1"); // NOI18N

        panelCentral.setBackground(resourceMap.getColor("panelCentral.background")); // NOI18N
        panelCentral.setFont(resourceMap.getFont("panelCentral.font")); // NOI18N
        panelCentral.setForeground(resourceMap.getColor("panelCentral.foreground")); // NOI18N
        panelCentral.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        panelCentral.setText(resourceMap.getString("panelCentral.text")); // NOI18N
        panelCentral.setBorder(new javax.swing.border.SoftBevelBorder(javax.swing.border.BevelBorder.RAISED));
        panelCentral.setDisabledIcon(resourceMap.getIcon("panelCentral.disabledIcon")); // NOI18N
        panelCentral.setName("panelCentral"); // NOI18N

        lblSituation.setFont(resourceMap.getFont("lblSituation.font")); // NOI18N
        lblSituation.setForeground(resourceMap.getColor("lblSituation.foreground")); // NOI18N
        lblSituation.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        lblSituation.setText(resourceMap.getString("lblSituation.text")); // NOI18N
        lblSituation.setName("lblSituation"); // NOI18N

        javax.swing.GroupLayout mainPanelLayout = new javax.swing.GroupLayout(mainPanel);
        mainPanel.setLayout(mainPanelLayout);
        mainPanelLayout.setHorizontalGroup(
            mainPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(mainPanelLayout.createSequentialGroup()
                .addGroup(mainPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(mainPanelLayout.createSequentialGroup()
                        .addGap(154, 154, 154)
                        .addGroup(mainPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(mainPanelLayout.createSequentialGroup()
                                .addComponent(txtPass, javax.swing.GroupLayout.PREFERRED_SIZE, 123, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(butPass))
                            .addGroup(mainPanelLayout.createSequentialGroup()
                                .addGap(10, 10, 10)
                                .addComponent(panelCentral, javax.swing.GroupLayout.PREFERRED_SIZE, 125, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addComponent(jLabel1, javax.swing.GroupLayout.PREFERRED_SIZE, 132, javax.swing.GroupLayout.PREFERRED_SIZE)))
                    .addGroup(mainPanelLayout.createSequentialGroup()
                        .addGap(60, 60, 60)
                        .addComponent(lblSituation, javax.swing.GroupLayout.PREFERRED_SIZE, 322, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap(106, Short.MAX_VALUE))
        );
        mainPanelLayout.setVerticalGroup(
            mainPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(mainPanelLayout.createSequentialGroup()
                .addGap(88, 88, 88)
                .addComponent(lblSituation, javax.swing.GroupLayout.PREFERRED_SIZE, 27, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(29, 29, 29)
                .addComponent(jLabel1)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(mainPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(butPass)
                    .addComponent(txtPass, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(50, 50, 50)
                .addComponent(panelCentral, javax.swing.GroupLayout.PREFERRED_SIZE, 31, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(56, Short.MAX_VALUE))
        );

        menuBar.setName("menuBar"); // NOI18N

        fileMenu.setText(resourceMap.getString("fileMenu.text")); // NOI18N
        fileMenu.setName("fileMenu"); // NOI18N

        exitMenuItem.setAction(actionMap.get("quit")); // NOI18N
        exitMenuItem.setName("exitMenuItem"); // NOI18N
        fileMenu.add(exitMenuItem);

        menuBar.add(fileMenu);

        helpMenu.setText(resourceMap.getString("helpMenu.text")); // NOI18N
        helpMenu.setName("helpMenu"); // NOI18N

        aboutMenuItem.setAction(actionMap.get("showAboutBox")); // NOI18N
        aboutMenuItem.setName("aboutMenuItem"); // NOI18N
        helpMenu.add(aboutMenuItem);

        menuBar.add(helpMenu);

        statusPanel.setName("statusPanel"); // NOI18N
        statusPanel.setPreferredSize(new java.awt.Dimension(0, 0));

        statusPanelSeparator.setName("statusPanelSeparator"); // NOI18N

        statusMessageLabel.setName("statusMessageLabel"); // NOI18N

        statusAnimationLabel.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
        statusAnimationLabel.setName("statusAnimationLabel"); // NOI18N

        progressBar.setName("progressBar"); // NOI18N

        javax.swing.GroupLayout statusPanelLayout = new javax.swing.GroupLayout(statusPanel);
        statusPanel.setLayout(statusPanelLayout);
        statusPanelLayout.setHorizontalGroup(
            statusPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(statusPanelSeparator, javax.swing.GroupLayout.DEFAULT_SIZE, 488, Short.MAX_VALUE)
            .addGroup(statusPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(statusMessageLabel)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 318, Short.MAX_VALUE)
                .addComponent(progressBar, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(statusAnimationLabel)
                .addContainerGap())
        );
        statusPanelLayout.setVerticalGroup(
            statusPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(statusPanelLayout.createSequentialGroup()
                .addComponent(statusPanelSeparator, javax.swing.GroupLayout.PREFERRED_SIZE, 2, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addGroup(statusPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(statusMessageLabel)
                    .addComponent(statusAnimationLabel)
                    .addComponent(progressBar, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(3, 3, 3))
        );

        setComponent(mainPanel);
        setMenuBar(menuBar);
        setStatusBar(statusPanel);
    }// </editor-fold>//GEN-END:initComponents

    @Action
    public void Click() {
        int i, card;
        try
        {
            card = Integer.decode(txtPass.getText());
            if(card != -1)
            {
                if(card == recent_card)
                {
                    gc_index = 'r';
                    is_move_made = true;
                }
                else
                {
                    for(i = 0; i < 4; i++)
                        if(card == user_cards[player_id][i])
                            break;

                    if(i != 4)
                    {
                        gc_index = i;
                        is_move_made = true;
                    }
                }
            }
        }
        catch(Exception e)
        {  }
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton butPass;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel lblSituation;
    private javax.swing.JPanel mainPanel;
    private javax.swing.JMenuBar menuBar;
    public javax.swing.JLabel panelCentral;
    private javax.swing.JProgressBar progressBar;
    private javax.swing.JLabel statusAnimationLabel;
    private javax.swing.JLabel statusMessageLabel;
    public javax.swing.JPanel statusPanel;
    private javax.swing.JTextField txtPass;
    // End of variables declaration//GEN-END:variables

    private final Timer messageTimer;
    private final Timer busyIconTimer;
    private final Icon idleIcon;
    private final Icon[] busyIcons = new Icon[15];
    private int busyIconIndex = 0;

    private JDialog aboutBox;

    // My definitions and declarations
    private agnInterface game_inter = new agnInterface();
    private int player_id, player_count, game_order = 0;
    private int user_cards[][], recent_card = -1, going_card = -1, gc_index = -1;
    javax.swing.JLabel user_panels[];
    private boolean is_move_made = false;
}