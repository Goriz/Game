using UnityEngine;
using System.Collections;

public class StatusMove : MonoBehaviour {
	
	private PlatformerCharacter2D  character;

	public const float moveStartTime = 1;
	private float movingTime = 0;

	
	// Use this for initialization
	void Start () {
		character = GetComponent<PlatformerCharacter2D>();

	}
	
	void FixedUpdate () {
		if(character && movingTime > moveStartTime){
			//jump relasions
			bool jump = Random.value > 0.92f;
			if(jump){
				character.Move(0,false,jump);
			}

			movingTime = 0;
		}
		movingTime += Time.deltaTime;
	}
}
