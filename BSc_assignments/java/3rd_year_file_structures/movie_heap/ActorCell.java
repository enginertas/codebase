import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

class ActorCell
{
    private Actor[] array;
    private int cur;
    private int fileNo;
    private int size;
    private BufferedReader input;
   
    public ActorCell(int pieces, int no) throws FileNotFoundException, IOException	//creates an ActorCell containing Actors from runfiles
    {
        cur=0;
        
        array=new Actor[pieces];
        fileNo=no;
        size=pieces;

        input =new BufferedReader(new FileReader("actorNameFile_run"+ Integer.toString(fileNo) +".txt"));
        
        loadNewElements();
    }
    private Boolean isEmpty()		//returns true if we have no actors in ActorCell
    {
        return cur==size;
    }

    public void loadNewElements() throws IOException		//loads new Actors from run files to the cell
    {
        int i, id;
        String str, actorName;

        for(i=0;i<size;i++)
        {
            if(input.ready())
            {
                str=input.readLine();
                id=Integer.parseInt(str.substring(0,5).trim());
                actorName=str.substring(6).trim();

                array[i]= new Actor(id, actorName);
            }
            
            else
            {
                size=i;
                break;
            }
        }
        cur=0;
    }
    public Actor getFirst()		//pops the first actor in the cell (actor with the smallest id) and returns it
    {
        Actor tmp;

        tmp=array[cur];
        array[cur]=null;
        cur++;

        return tmp;
    }

    public int getId() throws IOException	//gets the id of first actor in the cell(actor with the smallest id)
    {
        if(isEmpty())
        {
            loadNewElements();
            if(isEmpty())
                return -1;
        }

        return array[cur].getId();
    }
};
