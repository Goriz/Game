using UnityEngine;
using System.Collections;

public class ParcticalSystem1 : MonoBehaviour {

	// Use this for initialization
	void Start () {
		particleSystem.renderer.sortingLayerName = "Background";
		particleSystem.renderer.sortingOrder = 5;
	}
}
