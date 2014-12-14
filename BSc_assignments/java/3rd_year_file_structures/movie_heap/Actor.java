public class Actor
{
	private int actorId;
	private String actorName;
	
	public Actor(int id, String name)	//constructs an Actor object
	{
		actorId = id;
		actorName=name;
	}
	
	public int getId()		//returns actorId of an Actor object
	{
		return actorId;
	}

	public String getActor()	//returns actorName of an Actor object
	{
		return actorName;
	}
};
