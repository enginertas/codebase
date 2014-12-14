import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class MovieHeap
{
    private Movie[] array;
    private int cur;

    private void swap(int ind1, int ind2)		//swaps the index of two elements in array
    {
        Movie tmp=array[ind1];
        array[ind1]=array[ind2];
        array[ind2]=tmp;
    }

    public MovieHeap()		//constructs an MovieHeap
    {
        array= new Movie[1501];
        cur=1;
    }

    private Movie popMin()		//pops the movie with minimum id(at the head) in heap array
    {
        int i=1, d, swapWith;
        Movie tmp;

        tmp = array[1];
        cur--;

        swap(1,cur);

        while(i<cur)
        {
            d= 2*i;
            swapWith=d+1;
            if(d<cur)
            {
                if(swapWith<cur)
                {
                    if(array[d].getId()<array[swapWith].getId())
                        swapWith=d;
                }
                else
                    swapWith=d;
            }
            else
                swapWith = 0;

            if(swapWith==0)
                break;
            else if(array[i].getId()>=array[swapWith].getId())
                swap(i,swapWith);
            else
                break;

            i=swapWith;
        }

        array[cur]=null;
        return tmp;
    }
    public void writeFile(int files) throws IOException			//writes the current heap to file
    {
        int i;
        BufferedWriter out= new BufferedWriter(new FileWriter("movieRatingFile_heap"+ Integer.toString(files)+ ".txt" ));

        for(i=1; i<cur; i++)
        {
            out.write(String.format("%-5s",Integer.toString(array[i].getId())));
            out.write("$");
            out.write(String.format("%-40s",array[i].getMovie()));
            out.write("$");
            out.write(String.format("%-5s",Integer.toString(array[i].getRating())));
            out.write("\n");
        }
        out.close();
    }


    public void writeRunFile(int files) throws IOException		//writes the initial sorted movie segment to the file
    {
        BufferedWriter out= new BufferedWriter(new FileWriter("movieRatingFile_run"+ Integer.toString(files)+ ".txt" ));
        Movie mov;

        while(!isEmpty())
        {
            mov=popMin();

            out.write(String.format("%-5s",Integer.toString(mov.getId())));
            out.write("$");
            out.write(String.format("%-40s",mov.getMovie()));
            out.write("$");
            out.write(String.format("%-5s",Integer.toString(mov.getRating())));
            out.write("\n");
        }
        out.close();
    }
    public void insert(Movie mov)		//inserts a new movie to the heap
    {
        int child, parent;
        array[cur]=mov;

        child=cur;
        parent= cur/2;

        while(child!=1 && array[child].getId()<=array[parent].getId())
        {
            swap(child,parent);

            child=parent;
            parent/=2;
        }

        cur++;
    }

    public Boolean isAvailable()		//returns true if there exist any available spaces in the heap
    {
        return cur<=1500;
    }

    public Boolean isEmpty()			//returns true if the heap has no elements
    {
        return cur==1;
    }
};
