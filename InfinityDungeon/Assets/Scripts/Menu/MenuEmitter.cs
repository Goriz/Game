using UnityEngine;
using System.Collections;

public class MenuEmitter : MonoBehaviour {
	public enum CharacterId{
		Player,
		Enemy,
		Random
	}

	public GameObject player;
	public GameObject enemy;

	void Start(){
		CreateCharacter(CharacterId.Player);
	}

	public void CreateCharacter(CharacterId id){

		switch(id){
		case CharacterId.Player:
			Create(player);
			break;

		case CharacterId.Enemy:
			Create(player);
			break;

		default:
			//nothing
			break;
		}
	}

	private void Create(GameObject obj){

		Instantiate(obj,transform.position,transform.rotation);
	}

}
