﻿using UnityEngine;
using System.Collections;

public class Enemy : MonoBehaviour {

	public int hp = 10;
	public int attack = 1;
	public float speed = 5f;

	
	// アニメーターコンポーネント
	private Animator animator;
	private int doWalkId;
	private Vector2 director;
	private GameObject collider;

	// Use this for initialization
	void Start () {
		// アニメーターコンポーネントを取得
		animator = GetComponent<Animator> ();

		doWalkId = Animator.StringToHash ("DoWalk");

		director = new Vector2 (0, 0);
	}
	
	// Update is called once per frame
	void Update () {
		if (0 != transform.position.x) {
			animator.SetBool(doWalkId, true);
		}else{
			animator.SetBool(doWalkId, false);
		}
		
		transform.position = Vector2.MoveTowards(transform.position, director, speed * Time.deltaTime);

		// ヒットポイントが0以下であれば
		if(hp <= 0 )
		{
			// エネミーの削除
			Destroy (gameObject);
		}
	}
	
	void OnTriggerStay2D (Collider2D c)
	{

		animator.SetTrigger ("Attack");

	}

	void OnTriggerEnter2D(Collider2D c){
		print("Enter2D");
		director = new Vector2 (transform.position.x, transform.position.y);
		//director = c.gameObject.transform.position;
		collider = c.gameObject;
		}

	// After attack animation
	void Attack()
	{
		print ("attack");
		collider.gameObject.SendMessage("ApplyDamage", attack);
	}

	void ApplyDamage(int damage)
	{
		hp = hp - damage;
	}

}
