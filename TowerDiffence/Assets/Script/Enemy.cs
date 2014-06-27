using UnityEngine;
using System.Collections;

public class Enemy : MonoBehaviour {

	public int hp = 10;
	public int attack = 1;
	public float speed = 5f;

	public int L_or_R = 1;
	private int LEFT = 1, RIGHT = 2;
	
	// アニメーターコンポーネント
	private Animator animator;
	private int doWalkId;
	private Vector2 director;
	private GameObject collider = null;
	private bool col = false;

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

		if (collider != null && col == false) 
		{
			director = collider.transform.position;
		}
		
		transform.position = Vector2.MoveTowards(transform.position, director, speed * Time.deltaTime);

		// ヒットポイントが0以下であれば
		if(hp <= 0 )
		{
			// エネミーの削除
			Destroy (gameObject);
		}

		if(director.x < transform.position.x && L_or_R == RIGHT){
			Reverse();
			L_or_R = LEFT;
		}
		if(director.x > transform.position.x && L_or_R == LEFT){
			Reverse();
			L_or_R = RIGHT;
		}
	}

	void Reverse(){
		transform.Rotate(0, 180, 0);
	}
	
	void OnTriggerStay2D (Collider2D c)
	{
		director = transform.position;
		animator.SetTrigger ("Attack");

	}

	void OnTriggerEnter2D(Collider2D c){
		col = true;
		collider = c.gameObject;
		}

	void OnTriggerExit2D(Collider2D c){
		col = false;
		}

	// After attack animation
	void Attack()
	{
		if (collider != null) 
		{
			print ("attack");
			collider.gameObject.SendMessage ("ApplyDamage", attack);
		}
	}

	void ApplyDamage(int damage)
	{
		hp = hp - damage;
	}

}
