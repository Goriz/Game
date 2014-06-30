using UnityEngine;
using System.Collections;

public class StageSelect : MonoBehaviour {

	// Use this for initialization
	void Start () {

	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetMouseButtonDown (0)) {
			Vector2 tapPoint = Camera.main.ScreenToWorldPoint(Input.mousePosition);
			Collider2D collition2d = Physics2D.OverlapPoint(tapPoint);
			if (collition2d) {
				RaycastHit2D hitObject = Physics2D.Raycast(tapPoint,-Vector2.up);
				if (hitObject) {
					Debug.Log("hit object is " + hitObject.collider.gameObject.name);
					string stage_name = hitObject.collider.gameObject.name;

					if(stage_name == "stage1"){
						Application.LoadLevel ("TowerDiffence");
					}else if(stage_name == "stage2"){
						Application.LoadLevel ("TowerDiffence2");
					}else if(stage_name == "stage3"){
						Application.LoadLevel ("Title");
					}else if(stage_name == "stage4"){
						Application.LoadLevel ("Title");
					}else if(stage_name == "stage5"){
						Application.LoadLevel ("Title");
					}else if(stage_name == "stage6"){
						Application.LoadLevel ("Title");
					}else if(stage_name == "stage7"){
						Application.LoadLevel ("Title");
					}else if(stage_name == "stage8"){
						Application.LoadLevel ("Title");
					}else if(stage_name == "stage9"){
						Application.LoadLevel ("Title");
					}else if(stage_name == "stage10"){
						Application.LoadLevel ("Title");
					}else{
						print("Not select staged");
					}
			}
		}
	}
}
}
