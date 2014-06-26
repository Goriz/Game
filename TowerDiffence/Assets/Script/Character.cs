using UnityEngine;
using System.Collections;

public class Character : MonoBehaviour {

	private Vector2 director;
	// アニメーターコンポーネント
	private Animator animator;
	private int doWalkId;
	private int L_or_R = 1;
	private int LEFT = 1, RIGHT = 2;
	private Vector2 rotation;
	private Vector2 current_target;
	private GameObject collider;

	public float speed = 5f;
	public int attack = 5;
	public int hp = 10;
	int sumdamage = 0;

	// Use this for initialization
	void Start () {
		director = transform.position;
		// アニメーターコンポーネントを取得
		animator = GetComponent<Animator> ();

		doWalkId = Animator.StringToHash ("DoWalk");

		current_target = transform.position;
	}
	
	// Update is called once per frame
	void Update () {
		transform.position = Vector2.MoveTowards(transform.position, director, speed * Time.deltaTime);
		
		if (Input.GetMouseButtonDown(0)) {
			Vector2 tapPoint = Camera.main.ScreenToWorldPoint(Input.mousePosition);
			Collider2D collition2d = Physics2D.OverlapPoint(tapPoint);
			if (collition2d) {
				RaycastHit2D hitObject = Physics2D.Raycast(tapPoint,-Vector2.up);
				if (hitObject) {
					Debug.Log("hit object is " + hitObject.collider.gameObject.name);
					director = hitObject.collider.gameObject.transform.position;
				}
			}else{
				director = tapPoint;
			}
		}

		if (director.x != transform.position.x) {
				animator.SetBool(doWalkId, true);
			}else{
				animator.SetBool(doWalkId, false);
			}

		if(director.x < transform.position.x && L_or_R == RIGHT){
			Reverse();
			L_or_R = LEFT;
		}
		if(director.x > transform.position.x && L_or_R == LEFT){
			Reverse();
			L_or_R = RIGHT;
		}

		// ヒットポイントが0以下であれば
		if(hp <= 0 )
		{
			// エネミーの削除
			Destroy (gameObject);
		}
	}

	void Reverse(){
		transform.Rotate(0, 180, 0);
		}

	void OnTriggerStay2D (Collider2D c)
	{
			animator.SetTrigger ("Attack");
	}

	void OnTriggerEnter2D (Collider2D c)
	{
		collider = c.gameObject;
	}

	// After attack animation
	void Attack()
	{
		if (collider != null) {
			print ("attack");
			collider.gameObject.SendMessage ("ApplyDamage", attack);
		}
	}


	void ApplyDamage(int damage)
	{
		hp = hp - damage;
		sumdamage = sumdamage + damage;
	}
		
}
