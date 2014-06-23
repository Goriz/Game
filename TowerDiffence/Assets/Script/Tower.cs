using UnityEngine;
using System.Collections;

public class Tower : MonoBehaviour {

	public int hp = 1;

	int sumdamage = 0;

	// Use this for initialization
	void Start () {

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
	}
}
