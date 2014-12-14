import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

class MovieCell
{
    private Movie[] array;
    private int cur;
    private int fileNo;
    private int size;
    private BufferedReader input;

    public MovieCell(int pieces, int no) throws FileNotFoundException, IOException	//creates a MovieCell containing Movies from runfiles
    {
        cur=0;

        array=new Movie[pieces];
        fileNo=no;
        size=pieces;

        input =new BufferedReader(new FileReader("movieRatingFile_run"+ Integer.toString(fileNo) +".txt"));

        loadNewElements();
    }
    private Boolean isEmpty()		//returns true if we have no movies in MovieCell
    {
        return cur==size;
    }

    public void loadNewElements() throws IOException		//loads new Movies from run files to the cell
    {
        int i, id, rating;
        String str, movieName;

        for(i=0;i<size;i++)
        {
            if(input.ready())
            {
                str=input.readLine();
                id=Integer.parseInt(str.substring(0,5).trim());
                movieName=str.substring(6,46).trim();
                rating=Integer.parseInt(str.substring(47).trim());

                array[i]= new Movie(id, movieName, rating);
            }

            else
            {
                size=i;
                break;
            }
        }
        cur=0;
    }
    public Movie getFirst()			//pops the first movie in the cell (movie with the smallest id) and returns it
    {
        Movie tmp;

        tmp=array[cur];
        array[cur]=null;
        cur++;

        return tmp;
    }

    public int getId() throws IOException		//gets the id of first movie in the cell(movie with the smallest id)
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
