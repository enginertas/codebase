public class Movie
{
	private int actorId;
	private String movieName;
	private int rating;
	
	public Movie(int id, String name, int rat)	//constructs a movie object
	{
		actorId=id;
		movieName=name;
		rating=rat;
	}
	
	public int getId()		//returns actorId of corresponding movie object
	{
		return actorId;
	}
	
	public String getMovie()	//returns movieName of corresponding movie object
	{
		return movieName;
	}
	
	public int getRating()		//returns rating of corresponding movie object
	{
		return rating;
	}
};
