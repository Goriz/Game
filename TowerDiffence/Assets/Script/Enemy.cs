using UnityEngine;
using System.Collections;

public class Enemy : MonoBehaviour {

	public int hp = 100;
	public float speed = 5f;
	
	// アニメーターコンポーネント
	private Animator animator;
	private int doWalkId;
	private Vector2 director;

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
	}
	
	void OnTriggerStay2D (Collider2D c)
	{

		animator.SetTrigger ("Attack");

		director = c.gameObject.transform.position;

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
