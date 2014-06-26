using UnityEngine;
using System.Collections;

public class Character : MonoBehaviour {
	
	// アニメーターコンポーネント
	private Animator animator;
	private int doWalkId;
	private int director = 1;
	private int LEFT = 1, RIGHT = 2;
	private GotoMouse gotomouse;
	private Vector2 rotation;
	private Vector2 current_target;

	public int attack = 1;
	public int hp = 1;
	int sumdamage = 0;

	// Use this for initialization
	void Start () {
		// アニメーターコンポーネントを取得
		animator = GetComponent<Animator> ();

		doWalkId = Animator.StringToHash ("DoWalk");

		gotomouse = GetComponent<GotoMouse> ();

		current_target = transform.position;
	}
	
	// Update is called once per frame
	void Update () {
		if (gotomouse.getTarget().x != transform.position.x) {
				animator.SetBool(doWalkId, true);
			}else{
				animator.SetBool(doWalkId, false);
			}


		if(gotomouse.getTarget().x < transform.position.x && director == RIGHT){
			Reverse();
			director = LEFT;
		}
		if(gotomouse.getTarget().x > transform.position.x && director == LEFT){
			Reverse();
			director = RIGHT;
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


	void ApplyDamage(int damage)
	{
		hp = hp - damage;
		sumdamage = sumdamage + damage;
	}
}
