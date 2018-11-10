$(function () {

	const scene = new THREE.Scene();
	const camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight , 0.1, 1000);
	const renderer = new THREE.WebGLRenderer();
	renderer.setClearColor(new THREE.Color(0Xcccccc));
	renderer.setSize(window.innerWidth, window.innerHeight);
  renderer.shadowMapEnabled = true;

  const axes = new THREE.AxisHelper(20);
	scene.add(axes);

	const planeGeometry = new THREE.PlaneGeometry(60, 40, 1, 1);
	const planeMaterial = new THREE.MeshLambertMaterial({
    color: 'pink',
    // wireframe: true,
  });
  const plane = new THREE.Mesh(planeGeometry, planeMaterial);

	plane.rotation.x = -0.5 * Math.PI;
	plane.position.x = 15;
	plane.position.y = 0;
	plane.position.z = 0;
	scene.add(plane);

	const cubeGeometry = new THREE.CubeGeometry(4, 4, 4);
	const cubeMaterial = new THREE.MeshBasicMaterial({
    color: 0xff0000,
    // wireframe: true,
  });

	const cube = new THREE.Mesh(cubeGeometry, cubeMaterial);
	cube.position.x = -4;
	cube.position.y = 3;
	cube.position.z = 0;
  cube.castShadow = true;
	scene.add(cube);

	const sphereGeometry = new THREE.SphereGeometry(4,20,20);
	const sphereMaterial = new THREE.MeshBasicMaterial({
    color: 0x7777ff,
    wireframe: true,
  });

	const sphere = new THREE.Mesh(sphereGeometry,sphereMaterial);
	sphere.position.x = 20;
	sphere.position.y = 4;
	sphere.position.z = 2;
	scene.add(sphere);

  const spotLight = new THREE.SpotLight(0xffffff);
  spotLight.position.set(-40, 60, -10);
  spotLight.castShadow = true;
  scene.add(spotLight);

	camera.position.x = -30;
	camera.position.y = 40;
	camera.position.z = 30;
  camera.rotaion = {
    x: 0,
    y: 0,
    z: 0,
  }
	camera.lookAt(scene.position);





	$("#WebGL-output").append(renderer.domElement);
	renderer.render(scene, camera);

  var step=0;
  function render() {

  	step+=0.04;
  	sphere.position.x = 20+( 10*(Math.cos(step)));
  	sphere.position.y = 2 +( 10*Math.abs(Math.sin(step)));

    // camera.rotation.y -= 0.02;

  	requestAnimationFrame(render);
  	renderer.render(scene, camera);
  }
  render()


  $(document).keydown(function(e) {
    switch(e.which) {
        case 37: // left
        camera.rotation.y -= 0.02;
        break;

        case 38: // up
        camera.rotation.x += 0.02;
        break;

        case 39: // right
        camera.rotation.y += 0.02;
        break;

        case 40: // down
        camera.rotation.x -= 0.02;
        break;

        default: return; // exit this handler for other keys
    }
    renderer.render(scene, camera);
    console.log(camera.position)
    e.preventDefault(); // prevent the default action (scroll / move caret)
  });
});
