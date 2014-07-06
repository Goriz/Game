using UnityEngine;
using System.Collections;

public class MenuCharaMove : MonoBehaviour {

	private PlatformerCharacter2D  character;

	Transform rightSide;
	[SerializeField] LayerMask whatIsGround;	
	float sideRadious = .02f;

	// Use this for initialization
	void Start () {
		character = GetComponent<PlatformerCharacter2D>();

		rightSide = transform.Find("RightSideCheck"); //right side collision checker
	}

	void FixedUpdate () {
		if(character){

			bool jump = false;

			jump = Physics2D.OverlapCircle(rightSide.position,sideRadious,whatIsGround);

			character.Move(1,false,jump);

		}
	}
}
