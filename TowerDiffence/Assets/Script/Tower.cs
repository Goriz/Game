using UnityEngine;
using System.Collections;

public class Tower : MonoBehaviour {

	public int hp = 1;
	public int sumdamage = 0;
	int parcent = 1;

	private Gage towergage = null;

	// Use this for initialization
	void Start () {
		towergage = GetComponent<Gage> ();

	}
	
	// Update is called once per frame
	void Update () {
		// ヒットポイントが0以下であれば
		if(hp <= 0 )
		{
			Destroy (gameObject);
		}

	}

	void ApplyDamage(int damage)
	{
		hp = hp - damage;
		sumdamage = sumdamage + damage;
		parcent = sumdamage / hp;

		//towergage.gameObject.SendMessage("gageControl", parcent);
	}
	
}
