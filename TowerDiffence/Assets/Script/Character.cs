using UnityEngine;
using System.Collections;

public class Character : MonoBehaviour {
	
	// アニメーターコンポーネント
	private Animator animator;
	private int doWalkLeftId, doWalkRightId;
	private GotoMouse gotomouse;

	public int attack = 1;

	// Use this for initialization
	void Start () {
		// アニメーターコンポーネントを取得
		animator = GetComponent<Animator> ();
		doWalkLeftId = Animator.StringToHash ("DoWalkLeft");
		doWalkRightId = Animator.StringToHash ("DoWalkRight");

		gotomouse = GetComponent<GotoMouse> ();
	}
	
	// Update is called once per frame
	void Update () {
			if (Input.GetMouseButton(0)) {
				animator.SetBool(doWalkLeftId, true);
			}else{
				animator.SetBool(doWalkLeftId, false);
			}
	}
	
	// ぶつかった瞬間に呼び出される
	void OnTriggerStay2D (Collider2D c)
	{
			animator.SetTrigger ("Attack");
			
	}
}
