class Final
{
    private int actorId;
    private String actorName;
    private String movieName;
    private int rating;

    public Final(int id, String actor,String movie,int rat)		//constructs a new Final object(composition of Actor & Movie)
    {
        actorId=id;
        actorName=actor;
        movieName=movie;
        rating=rat;
    }

    public int getId()		//gets actorId of Final objects
    {
        return actorId;
    }

    public String getActor()	//gets actorName of Final objects
    {
        return actorName;
    }

    public String getMovie()	//gets movieName of Final objects
    {
        return movieName;
    }
    
    public int getRating()	//gets rating of Final objects
    {
        return rating;
    }
};
