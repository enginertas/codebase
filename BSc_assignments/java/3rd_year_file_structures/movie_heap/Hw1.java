import javax.xml.stream.*;
import javax.xml.stream.events.*;
import javax.xml.stream.XMLInputFactory;
import java.io.*;
import java.util.Vector;

public class Hw1
{
        private static int actorFiles=1;
        private static int movieFiles=1;

        private static void actorXMLParser(String actorFile) throws FileNotFoundException, XMLStreamException, IOException
        {
                int areaType=0, currentId=0;		//parses actorName file, creates Actor objects, creates heapfiles and runfiles of Actors
                String current, currentName = null;
                Actor act=null;
                ActorHeap actHeap= new ActorHeap();

		XMLInputFactory inpFactory =XMLInputFactory.newInstance();
                InputStream inputStr = new FileInputStream(actorFile);
                XMLEventReader inputParser = inpFactory.createXMLEventReader(inputStr);

                while(inputParser.hasNext())
                {
                    XMLEvent e = inputParser.nextEvent();
                    switch(e.getEventType())
                    {
                        case XMLEvent.START_DOCUMENT:
                            areaType=0;
                            break;

                        case XMLEvent.START_ELEMENT:
                            current = e.toString();

                            if(current.equals("<actorid>"))
                                areaType=1;
                            else if (current.equals("<actorname>"))
                                areaType=2;
                            else areaType=0;

                            break;

                        case XMLEvent.END_ELEMENT:
                            current=e.toString();
                            if(current.equals("</actor>"))
                            {
                                act=new Actor(currentId, currentName);

                                if(actHeap.isAvailable())
                                    actHeap.insert(act);
                                else
                                {
                                    actHeap.writeFile(actorFiles);
                                    actHeap.writeRunFile(actorFiles);
                                    actorFiles++;

                                    actHeap.insert(act);
                                }
                            }
                            areaType=0;
                            break;

                        case XMLEvent.END_DOCUMENT:
                            actHeap.writeFile(actorFiles);
                            actHeap.writeRunFile(actorFiles);
                            areaType=0;
                            break;

                        case XMLEvent.CHARACTERS:
                            if(areaType==1)
                                currentId=Integer.parseInt(e.toString());
                            else if(areaType==2)
                                currentName=e.toString();

                            areaType=0;
                            break;

                        default:
                            areaType=0;
                    }
                }
        }

        private static void movieXMLParser(String movieFile) throws FileNotFoundException, XMLStreamException, IOException
        {
                int areaType=0, currentId=0, curRating=0;	//parses movieRating file, creates Movie objects, creates heapfiles and runfiles of Movies
                String current, currentName = null;
                Movie mov=null;
                MovieHeap movHeap= new MovieHeap();

		XMLInputFactory inpFactory =XMLInputFactory.newInstance();
                InputStream inputStr = new FileInputStream(movieFile);
                XMLEventReader inputParser = inpFactory.createXMLEventReader(inputStr);

                while(inputParser.hasNext())
                {
                    XMLEvent e = inputParser.nextEvent();
                    switch(e.getEventType())
                    {
                        case XMLEvent.START_DOCUMENT:
                            areaType=0;
                            break;

                        case XMLEvent.START_ELEMENT:
                            current = e.toString();

                            if(current.equals("<actorid>"))
                                areaType=1;
                            else if (current.equals("<moviename>"))
                                areaType=2;
                            else if (current.equals("<rating>"))
                                areaType=3;
                            else areaType=0;

                            break;

                        case XMLEvent.END_ELEMENT:
                            current=e.toString();
                            if(current.equals("</actor>"))
                            {
                                mov=new Movie(currentId, currentName, curRating);

                                if(movHeap.isAvailable())
                                    movHeap.insert(mov);
                                else
                                {
                                    movHeap.writeFile(movieFiles);
                                    movHeap.writeRunFile(movieFiles);
                                    movieFiles++;

                                    movHeap.insert(mov);
                                }
                            }
                            areaType=0;
                            break;

                        case XMLEvent.END_DOCUMENT:
                            movHeap.writeFile(movieFiles);
                            movHeap.writeRunFile(movieFiles);
                            areaType=0;
                            break;

                        case XMLEvent.CHARACTERS:
                            if(areaType==1)
                                currentId=Integer.parseInt(e.toString());
                            else if(areaType==2)
                                currentName=e.toString();
                            else if(areaType==3)
                                curRating=Integer.parseInt(e.toString());

                            areaType=0;
                            break;

                        default:
                            areaType=0;
                    }
                }
        }
        public static void kMerge() throws FileNotFoundException, IOException, XMLStreamException
        {
            int i,k, min, actIndex;		//applys k-merge algorithm on runfiles, merges them and writes to actors.XML file
            Vector actorCells= new Vector();
            Vector movieCells= new Vector();
            OutBuffer out= new OutBuffer();
            k=1000/(actorFiles+movieFiles);

            
            for(i=1; i<=actorFiles; i++)
            {
                ActorCell c = new ActorCell(k, i);
                actorCells.add(c);
            }

            for(i=1; i<=movieFiles; i++)
            {
                MovieCell c = new MovieCell(k,  i);
                movieCells.add(c);
            }

            actorFiles--; movieFiles--;
            while(movieFiles!=-1)
            {
                min=100000; actIndex=-1;

                for(i=0; i<=actorFiles; i++)
                {
                    k=((ActorCell)actorCells.get(i)).getId();
                    if(k==-1)
                    {
                        actorCells.remove(i);
                        actorFiles--;
                        min=100000; actIndex=-1;
                        i=-1;
                    }
                    else if(k<min)
                    {
                        min=k;
                        actIndex=i;
                    }
                }
                Actor act= ((ActorCell)actorCells.get(actIndex)).getFirst();
                
                for(i=0; i<=movieFiles; i++)
                {
                    k=((MovieCell)movieCells.get(i)).getId();
                    if(k==-1)
                    {
                        movieCells.remove(i);
                        movieFiles--;
                        i--;
                        
                    }
                    else if(k==min)
                    {
                        Movie mov=((MovieCell)movieCells.get(i)).getFirst();
                        Final fin= new Final(k, act.getActor(), mov.getMovie(), mov.getRating());

                        i--;
                        out.add(fin);
                    }
                }
            }
            out.endXML();
        }

	public static void main(String args[]) throws FileNotFoundException, XMLStreamException, IOException
	{
                String actorFile= args[0];		//main function
		String movieFile= args[1];

                actorXMLParser(actorFile);
                movieXMLParser(movieFile);

                kMerge();
	}
};
