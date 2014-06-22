using UnityEngine;
using System.Collections;

public class Enemy : MonoBehaviour {

	public int hp = 100;
	
	// アニメーターコンポーネント
	private Animator animator;

	// Use this for initialization
	void Start () {
		// アニメーターコンポーネントを取得
		animator = GetComponent<Animator> ();
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	// ぶつかった瞬間に呼び出される
	void OnTriggerStay2D (Collider2D c)
	{
		animator.SetTrigger ("Damage");	
		
		// ヒットポイントを減らす
		hp = hp - 1;


		// ヒットポイントが0以下であれば
		if(hp <= 0 )
		{
			// エネミーの削除
			Destroy (gameObject);
		}
	}
}
