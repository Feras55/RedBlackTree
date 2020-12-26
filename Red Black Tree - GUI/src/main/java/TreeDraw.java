
import javax.swing.*;
import java.awt.*;


class pair{
    int first;
    int second;
    pair(int f , int s){
        first=f;
        second=s;
    }
}
public class TreeDraw extends JFrame {
    RedBlackTree bst = new RedBlackTree();

    int width;
    int height;

    Node TNULL = new Node();


    public void paint(Graphics g) { // draw the nodes and edges
        g.clearRect(0, 80, getWidth(), getHeight());


        paint2(bst.getRoot(),new pair(500,100),250);
    }


    public void paint2(Node root,pair Pa, int space) { // draw the nodes and edges
        if(root!=TNULL){


        Graphics g =this.getGraphics();
        Color color = root.color == 1?Color.RED:Color.black;

        FontMetrics f = this.getGraphics().getFontMetrics();
        int nodeHeight = Math.max(height, f.getHeight());

        int nodeWidth = Math.max(width, f.stringWidth(String.valueOf(root.data))+width/2);
        g.setColor(Color.white);
        g.fillOval(Pa.first-nodeWidth/2, Pa.second-nodeHeight/2, nodeWidth, nodeHeight);
        g.setColor(color);
        g.drawOval(Pa.first-nodeWidth/2, Pa.second-nodeHeight/2, nodeWidth, nodeHeight);
        g.drawString(String.valueOf(root.data), Pa.first-f.stringWidth(String.valueOf(root.data))/2,
                Pa.second+f.getHeight()/2);

        if(root.left!=null){
            paint2(root.left,new pair(Pa.first-space,Pa.second+50),space/2);
            this.getGraphics().drawLine(Pa.first, Pa.second,
                    Pa.first-space, Pa.second+50);
        }
        if(root.right!=null){
            paint2(root.right,new pair(Pa.first +space,Pa.second+50),space/2);
            this.getGraphics().drawLine(Pa.first, Pa.second,
                    Pa.first +space, Pa.second+50);
        }
        }
    }

    public TreeDraw() { //Constructor
        this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        width = 30;
        height = 30;
    }

    public TreeDraw(String name) { //Construct with label
        this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        this.setName(name);
        this.setTitle(name);
        width = 30;
        height = 30;
        TNULL.color = 0;
        TNULL.left = null;
        TNULL.right = null;

    }



}

class testTreeDraw {

    public static void main(String[] args) {
        TreeDraw frame = new TreeDraw("Red Black Tree");
        frame.setSize(1000,800);

        frame.setResizable(false);


        frame.setLayout(new FlowLayout());

        frame.setSize(1000,600);

        JPanel pan=new JPanel();//contain all the buttons and text Fields



        //Add button,text Field and button action
        JButton add=new JButton("Add");
        JTextField addText=new JTextField();
        addText.setColumns(10);
        add.addActionListener(e -> {
            frame.bst.insert(Integer.parseInt(addText.getText()));
            frame.repaint();
        });

        //Delete button,text Field and button action
        JButton delete=new JButton("Delete");
        JTextField deleteText=new JTextField();
        deleteText.setColumns(10);
        delete.addActionListener(e -> {
            frame.bst.deleteNode(Integer.parseInt(deleteText.getText()));
            frame.repaint();
        });

        //Delete button,text Field and button action
        JButton clear=new JButton("Clear All");
        clear.addActionListener(e -> {
            frame.bst.clear();
            frame.repaint();
        });

        pan.add(addText);
        pan.add(add);
        pan.add(deleteText);
        pan.add(delete);
        pan.add(clear);


        frame.add(pan);

        pan.setBounds(1,1,50,50);
        pan.setVisible(true);
        frame.setVisible(true);
    }
}
