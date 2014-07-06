using UnityEngine;
using System.Collections;

[RequireComponent(typeof(BoxCollider2D))]
public class MenuRemover : MonoBehaviour {

	public MenuEmitter  emitter;

	void OnStart(){
		//emitter = FindObjectOfType<MenuEmitter>();
	}


	void OnTriggerEnter2D (Collider2D coll) {

		if (coll.gameObject.tag == "Player"){

			Destroy(coll.gameObject);

			emitter.SendMessage("CreateCharacter",MenuEmitter.CharacterId.Player);
		}
	}
}
