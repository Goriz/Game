﻿using UnityEngine;
using System.Collections;

public class Tower : MonoBehaviour {

	public float hp = 10;
	public float sumdamage = 0;
	private float max_hp;
	private float parcent = 1;
	private GameObject gage = null;

	// Use this for initialization
	void Start () {
		gage = GameObject.Find ("gage");
		max_hp = hp;
	}
	
	// Update is called once per frame
	void Update () {
		// ヒットポイントが0以下であれば
		if(hp <= 0 )
		{	
			FindObjectOfType<Score>().Save();

			Application.LoadLevel ("GameOver");
		}

	}

	void ApplyDamage(int damage)
	{
		hp = hp - damage;
		sumdamage = sumdamage + damage;
		parcent = hp / max_hp;

		gage.SendMessage("gageControl", parcent);
	}
	
}
