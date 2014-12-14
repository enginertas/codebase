import java.io.FileOutputStream;
import java.io.IOException;
import javax.xml.stream.*;
import javax.xml.stream.XMLOutputFactory;

public class OutBuffer
{
    private Final[] array;
    private int cur;
    private XMLStreamWriter strWriter;


    private Boolean isFull()		//returns true if buffer is full
    {
        return cur==500;
    }

    public OutBuffer() throws IOException, XMLStreamException		//creates a new output buffer which contains Final (Actor&Movie) objects
    {
        cur=0;
        array= new Final[500];

        XMLOutputFactory of =XMLOutputFactory.newInstance();
        strWriter=of.createXMLStreamWriter(new FileOutputStream("Actors.xml"),"ISO-8859-1");
        strWriter.writeStartDocument("ISO-8859-1","1.0");
        strWriter.writeCharacters("\n");
        strWriter.writeStartElement("actors");
    }

    public void add(Final fin)throws XMLStreamException		//adds a new Final object to output buffer
    {
        if(isFull())
            writeToXML();
        
        array[cur]=fin;
        cur++;
    }

    private void writeToXML() throws XMLStreamException			//writes all records in the buffer to the actors.XML file
    {
        int i;
        
        for(i=0; i<cur; i++)
        {
            strWriter.writeCharacters("\n    ");
            strWriter.writeStartElement("actor");
            strWriter.writeCharacters("\n        ");
            strWriter.writeStartElement("actorid");
            strWriter.writeCharacters(Integer.toString(array[i].getId()));
            strWriter.writeEndElement();
            strWriter.writeCharacters("\n        ");
            strWriter.writeStartElement("actorname");
            strWriter.writeCharacters(array[i].getActor());
            strWriter.writeEndElement();
            strWriter.writeCharacters("\n        ");
            strWriter.writeStartElement("moviename");
            strWriter.writeCharacters(array[i].getMovie());
            strWriter.writeEndElement();
            strWriter.writeCharacters("\n        ");
            strWriter.writeStartElement("rating");
            strWriter.writeCharacters(Integer.toString(array[i].getRating()));
            strWriter.writeEndElement();
            strWriter.writeCharacters("\n    ");
            strWriter.writeEndElement();

            array[i]=null;
        }
       
        strWriter.flush();
        cur=0;
    }

    public void endXML() throws XMLStreamException		//writes end of the file of actors.XML
    {
        writeToXML();
	
        strWriter.writeCharacters("\n");
        strWriter.writeEndElement();
        strWriter.writeEndDocument();
        strWriter.flush();
        strWriter.close();
    }
};
