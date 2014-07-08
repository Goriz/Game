using UnityEngine;
using System.Collections;

public class Enemy : MonoBehaviour {

	public int hp = 10;
	public int attack = 1;
	public float speed = 5f;
	public int point = 100;
	public GameObject item;

	public int L_or_R = 1;
	private int LEFT = 1, RIGHT = 2;
	
	// アニメーターコンポーネント
	private Animator animator;
	private int doWalkId;
	private Vector2 director;
	private GameObject collider = null;
	private bool col = false;
	private bool atk = false;

	// Use this for initialization
	IEnumerator Start () {
		// アニメーターコンポーネントを取得
		animator = GetComponent<Animator> ();

		doWalkId = Animator.StringToHash ("DoWalk");

		director = new Vector2 (0, 0);

		while (true) 
		{
			atk = false;
			if(col == true){
				atk = true;
				animator.SetTrigger ("Attack");
				yield return new WaitForSeconds(2.0f);
			}
			yield return new WaitForSeconds(0.05f);
		}
	}
	
	// Update is called once per frame
	void Update () {

		if (atk == false) {
			animator.SetBool(doWalkId, true);
		}else{
			animator.SetBool(doWalkId, false);
		}
		
		//When Attacked by Player
		if (collider != null && col == false) {
			director = collider.transform.position;
		}

		//When Player Destroy
		if (collider == null) {
			director = new Vector2 (0, 0);
		}

		//Not Attacking
		if (atk == false) {
			transform.position = Vector2.MoveTowards (transform.position, director, speed * Time.deltaTime);
		}

		// ヒットポイントが0以下であれば
		if(hp <= 0 )
		{
			// エネミーの削除
			animator.SetTrigger ("Dead");
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
			audio.Play();
			collider.gameObject.SendMessage ("ApplyDamage", attack);
		}
	}

	// After dead animation
	void Dead()
	{
		Destroy (gameObject);
		FindObjectOfType<Score>().AddPoint(point);

		Instantiate (item, transform.position, transform.rotation);
	}

	void ApplyDamage(int damage)
	{
		animator.SetTrigger ("Damage");
		hp = hp - damage;
	}

}
