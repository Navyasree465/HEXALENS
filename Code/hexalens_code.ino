import React, { useState, useEffect, useCallback, useMemo, useRef } from "react";

/* ----------------------------------------------------
 * Simple CSS injected at runtime
 * so this is a single-file app.
 * Tailwind CSS is preferred in general, but since the
 * user provided their own custom CSS, we will stick to it
 * and just make sure it's injected correctly.
 * ---------------------------------------------------- */
const injectedCSS = `
:root {
  --bg: #04040a;
  --panel: #0b1020;
  --gold: #f6c85f;
  --muted: #9aa4b2;
  --glass: rgba(255,255,255,0.04);
}
*{box-sizing:border-box}
html,body,#root {height:100%;}
body {
  margin:0;
  font-family: Inter,ui-sans-serif,system-ui, -apple-system, "Segoe UI", Roboto, "Helvetica Neue", Arial;
  background: #090A0F; /* Solid dark background for the base */
  color: #e6eef8;
  -webkit-font-smoothing:antialiased;
  overflow: hidden; /* Prevent scrollbars from stars */
  display: flex;
  align-items: center;
  justify-content: center;
}

/* NEW: Background Graphics */
.background-gradient {
  position: fixed;
  inset: 0;
  background: radial-gradient(ellipse at bottom, #1B2735 0%, #090A0F 100%);
  z-index: -20;
}

@keyframes animStar {
  from {
    transform: translateY(0px);
  }
  to {
    transform: translateY(-2000px);
  }
}

@keyframes twinkle {
  0%, 100% {
    opacity: 0.2;
    transform: scale(0.8);
  }
  50% {
    opacity: 1;
    transform: scale(1.2);
  }
}

@keyframes comet-anim {
  0% {
    transform: translate(50vw, -50vh) rotate(-45deg);
    opacity: 1;
  }
  100% {
    transform: translate(-100vw, 100vh) rotate(-45deg);
    opacity: 0;
  }
}

#stars, #stars2, #stars3, #twinkling-stars {
  position: absolute;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  width: 1px;
  height: 1px;
  background: transparent;
  z-index: -10;
}

#stars:after, #stars2:after, #stars3:after {
  content: " ";
  position: absolute;
  top: 2000px;
  background: transparent;
}

#stars {
  animation: animStar 150s linear infinite;
  box-shadow: 2331px 2333px #FFF, 203px 2997px #FFF, 1539px 2836px #FFF, 2458px 1196px #FFF, 258px 128px #FFF, 2339px 2798px #FFF, 2732px 1387px #FFF, 2226px 2431px #FFF, 1499px 1894px #FFF, 752px 2206px #FFF, 2302px 2235px #FFF, 1558px 1118px #FFF, 193px 2898px #FFF, 1643px 255px #FFF, 234px 1731px #FFF, 2373px 229px #FFF, 1613px 2892px #FFF, 2261px 113px #FFF, 1946px 2083px #FFF, 215px 2355px #FFF, 543px 894px #FFF, 1789px 1345px #FFF, 902px 345px #FFF, 134px 1879px #FFF;
}
#stars:after {
  width: 1px;
  height: 1px;
  box-shadow: 2331px 2333px #FFF, 203px 2997px #FFF, 1539px 2836px #FFF, 2458px 1196px #FFF, 258px 128px #FFF, 2339px 2798px #FFF, 2732px 1387px #FFF, 2226px 2431px #FFF, 1499px 1894px #FFF, 752px 2206px #FFF, 2302px 2235px #FFF, 1558px 1118px #FFF, 193px 2898px #FFF, 1643px 255px #FFF, 234px 1731px #FFF, 2373px 229px #FFF, 1613px 2892px #FFF, 2261px 113px #FFF, 1946px 2083px #FFF, 215px 2355px #FFF, 543px 894px #FFF, 1789px 1345px #FFF, 902px 345px #FFF, 134px 1879px #FFF;
}

#stars2 {
  width: 2px;
  height: 2px;
  animation: animStar 100s linear infinite;
  box-shadow: 233px 1827px #FFF, 1421px 1334px #FFF, 1204px 1201px #FFF, 1832px 211px #FFF, 1640px 1435px #FFF, 1491px 1139px #FFF, 1303px 1622px #FFF, 100px 1812px #FFF, 1803px 210px #FFF, 2862px 2226px #FFF, 456px 456px #FFF, 1999px 1000px #FFF;
}
#stars2:after {
  width: 2px;
  height: 2px;
  box-shadow: 233px 1827px #FFF, 1421px 1334px #FFF, 1204px 1201px #FFF, 1832px 211px #FFF, 1640px 1435px #FFF, 1491px 1139px #FFF, 1303px 1622px #FFF, 100px 1812px #FFF, 1803px 210px #FFF, 2862px 2226px #FFF, 456px 456px #FFF, 1999px 1000px #FFF;
}

#stars3 {
  width: 3px;
  height: 3px;
  animation: animStar 50s linear infinite;
  box-shadow: 267px 1469px #FFF, 1318px 2736px #FFF, 2315px 1481px #FFF, 2178px 1393px #FFF, 283px 244px #FFF, 1500px 500px #FFF;
}
#stars3:after {
  width: 3px;
  height: 3px;
  box-shadow: 267px 1469px #FFF, 1318px 2736px #FFF, 2315px 1481px #FFF, 2178px 1393px #FFF, 283px 244px #FFF, 1500px 500px #FFF;
}

#twinkling-stars {
  width: 1px;
  height: 1px;
  animation: twinkle 4s linear infinite;
  box-shadow: 83px 1827px #FFF, 141px 1334px #FFF, 120px 1201px #FFF, 183px 211px #FFF, 164px 1435px #FFF, 149px 1139px #FFF, 130px 1622px #FFF, 10px 1812px #FFF, 180px 210px #FFF, 286px 2226px #FFF, 1500px 800px #FFF, 1200px 1500px #FFF, 800px 500px #FFF;
}

.comet {
  position: fixed;
  top: 0;
  left: 50%;
  width: 3px;
  height: 200px;
  background: linear-gradient(to bottom, rgba(255, 255, 255, 0.5), transparent);
  border-radius: 50%;
  opacity: 0;
  animation: comet-anim 15s linear infinite;
  z-index: -5;
  transform-origin: top center;
}
.comet::before {
    content: '';
    position: absolute;
    top: -3px;
    left: 50%;
    transform: translateX(-50%);
    width: 6px;
    height: 6px;
    background: #fff;
    border-radius: 50%;
    box-shadow: 0 0 10px #fff, 0 0 20px #fff, 0 0 30px #00aaff;
}

.satellite {
    position: fixed;
    width: 50px;
    height: 20px;
    z-index: -4;
    animation: satellite-pass 45s linear infinite;
}
@keyframes satellite-pass {
    0% {
        transform: translate(-100px, 10vh);
    }
    100% {
        transform: translate(100vw, 15vh);
    }
}
.satellite-2 {
    animation-name: satellite-pass-2;
    animation-duration: 60s;
    animation-delay: 10s;
}
@keyframes satellite-pass-2 {
     0% {
        transform: translate(100vw, 80vh) rotate(15deg);
    }
    100% {
        transform: translate(-100px, 70vh) rotate(15deg);
    }
}
/* End Background Graphics */


.app {
  max-width:800px;
  margin: 0 auto;
}
.left {
  flex: 1;
  background: linear-gradient(180deg, rgba(255,255,255,0.02), transparent);
  border-radius:12px;
  padding:18px;
  box-shadow: 0 6px 30px rgba(0,0,0,0.6);
  display: flex;
  flex-direction: column;
  max-height: calc(100vh - 36px);
}
.header {
  display:flex;
  align-items:center;
  margin-bottom: 12px;
}
.title {
  font-size:20px;
  font-weight:700;
  color:var(--gold);
  display:flex;
  gap:8px;
  align-items:center;
  justify-content: center;
}
.controls {display:flex; gap:8px; align-items:center;}
.btn {
  background: linear-gradient(180deg, #162034, #0f1724);
  border:1px solid rgba(255,255,255,0.04);
  color:#e6eef8;
  padding:8px 12px;
  border-radius:8px;
  cursor:pointer;
  transition: transform 0.15s ease;
}
.btn:hover {
    transform: translateY(-2px);
}
.btn.primary { background: linear-gradient(180deg,var(--gold), #d4a646); color:#111; font-weight:700;}
.small { padding:6px 8px; font-size:13px; }
.hint { color:var(--muted); font-size:13px; margin-top:8px; }

.honey-wrap { 
    padding: 20px; 
    overflow-y: auto;
    flex-grow: 1;
}

.honey-wrap::-webkit-scrollbar {
  width: 8px;
}
.honey-wrap::-webkit-scrollbar-track {
  background: rgba(255,255,255,0.02);
  border-radius: 10px;
}
.honey-wrap::-webkit-scrollbar-thumb {
  background: var(--gold);
  border-radius: 10px;
}
.honey-wrap::-webkit-scrollbar-thumb:hover {
  background: #d4a646;
}

.hex-row {
  display: flex;
  justify-content: center;
  margin-bottom: -34px;
}
.big-hex {
  width:120px;
  height:138px;
  position:relative;
  transition: transform .15s ease;
  display:flex;
  align-items:center;
  justify-content:center;
  margin: 0 4px;
}
.big-hex:hover:not(.hex-complete):not(.hex-truly-locked) { transform: translateY(-6px); }
.hex-shape {
  width:100%;
  height:100%;
  clip-path: polygon(25% 0, 75% 0, 100% 50%, 75% 100%, 25% 100%, 0 50%);
  display:flex;
  align-items:center;
  justify-content:center;
  background: linear-gradient(180deg, rgba(255,255,255,0.02), rgba(255,255,255,0.01));
  border: 1px solid rgba(255,255,255,0.04);
  border-radius:6px;
  position:relative;
  box-shadow: 0 6px 18px rgba(0,0,0,0.6), inset 0 -6px 10px rgba(0,0,0,0.25);
}
.hex-locked { background: linear-gradient(180deg,#1b2435,#0b1220); color:var(--muted);}
.hex-complete { 
  box-shadow: 0 10px 30px rgba(214,166,70,0.18); 
  border: 2px solid var(--gold);
  transform: rotate(-2deg);
  background-size: cover;
  background-position: center;
}

.hex-truly-locked {
  background: linear-gradient(180deg, #0f1724, #04040a);
  cursor: not-allowed !important;
  color: #4a5568;
}
.hex-truly-locked:hover {
  transform: none !important;
}

.mini-grid {
  position:absolute;
  inset:0;
  display:grid;
  grid-template-columns: repeat(6, 1fr);
  grid-template-rows: repeat(3, 1fr);
  gap:2px;
  padding:2px;
  pointer-events:none;
}
.mini-hex-piece {
  clip-path: polygon(25% 0, 75% 0, 100% 50%, 75% 100%, 25% 100%, 0 50%);
  background-size: 300% 300%;
  transition: all 0.5s ease-out;
}

.modal-backdrop { position:fixed; inset:0; background:rgba(0,0,0,0.6); display:flex; align-items:center; justify-content:center; z-index:60; }
.modal {
  width: 760px;
  max-width: 95%;
  max-height: 80vh;
  overflow-y: auto;
  background: #071023;
  border-radius: 12px;
  padding: 18px;
  box-shadow: 0 12px 60px rgba(0,0,0,0.6);
  color: #eaf2ff;
  display: flex;
  flex-direction: column;
}
.question { font-size:16px; font-weight:700; margin-bottom:12px; }
.options { display:grid; grid-template-columns: 1fr 1fr; gap:10px; }
.option-btn { background: #091827; border:1px solid rgba(255,255,255,0.03); padding:10px; border-radius:8px; cursor:pointer; text-align:left; }
.option-btn:hover { transform:translateY(-2px); }

.full-image-modal {
  width: 90vw;
  max-width: 1200px;
  height: 90vh;
  background-color: var(--bg);
  border-radius: 12px;
  box-shadow: 0 12px 60px rgba(0,0,0,0.6);
  display: flex;
  flex-direction: column;
  overflow: hidden;
  padding: 20px;
  position: relative;
}
.full-image-modal img {
  width: 100%;
  height: auto;
  object-fit: contain;
  border-radius: 8px;
  max-height: 70vh;
}
.full-image-content {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  overflow-y: auto;
  padding: 10px;
}
.full-image-description {
  margin-top: 15px;
  font-size: 1rem;
  color: #e6eef8;
  text-align: center;
  padding: 0 20px;
}
.full-image-modal .close-btn {
  position: absolute;
  top: 10px;
  right: 10px;
  background: rgba(255,255,255,0.1);
  color: #fff;
  border: none;
  border-radius: 50%;
  width: 30px;
  height: 30px;
  font-size: 18px;
  cursor: pointer;
  z-index: 70;
}
.full-image-modal .close-btn:hover { background: rgba(255,255,255,0.2); }

.piece-reveal-modal {
  width: 500px;
  max-width: 95%;
  background: #071023;
  border-radius: 12px;
  padding: 18px;
  box-shadow: 0 12px 60px rgba(0,0,0,0.6);
  color: #eaf2ff;
  display: flex;
  flex-direction: column;
  align-items: center;
}
.piece-reveal-modal h3 { margin-top:0; }
.piece-reveal-modal .piece-img-container {
  width: 180px;
  height: 180px;
  position: relative;
  overflow: hidden;
  border: 2px solid var(--gold);
  border-radius: 12px;
}
.piece-reveal-modal .piece-img-container div {
  position: absolute;
  width: 300%;
  height: 300%;
}
.piece-reveal-modal .close-btn {
  margin-top: 20px;
}

.progress { height:12px; width:100%; background: rgba(255,255,255,0.04); border-radius:8px; overflow:hidden; margin-top:10px;}
.progress > div { height:100%; background: linear-gradient(90deg, var(--gold), #f0b84a); width:0; transition: width .3s ease;}

.panel-title { font-size:16px; font-weight:700; color:var(--gold); margin-bottom:8px; }
.fact { background:var(--glass); padding:10px; border-radius:8px; color:var(--muted); font-size:14px; line-height:1.6; }

.intro-screen, .start-screen, .level-selection {
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    text-align: center;
    gap: 15px;
    padding: 40px 20px;
    flex-grow: 1;
}
.intro-screen h2, .start-screen h2, .level-selection h2 {
    margin-top: 0;
    color: var(--gold);
}
.intro-screen .btn, .start-screen .btn, .level-selection .btn {
    width: 200px;
    font-size: 16px;
    padding: 12px;
}

.assembly-backdrop {
  position: fixed;
  inset: 0;
  background: rgba(0, 0, 0, 0.85);
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  z-index: 70;
  backdrop-filter: blur(8px);
}
.assembly-container {
  position: relative;
  width: 700px;
  height: 394px;
  transform: scale(0.9);
  transition: transform 0.3s ease;
}
@media (max-width: 768px) {
  .assembly-container {
    width: 90vw;
    height: 50.625vw;
  }
}
.assembly-piece {
  position: absolute;
  width: calc(100% / 6);
  height: calc(100% / 3);
  clip-path: polygon(25% 0, 75% 0, 100% 50%, 75% 100%, 25% 100%, 0 50%);
  background-size: 600% 300%;
  transition: all 1.5s cubic-bezier(0.68, -0.55, 0.27, 1.55);
  will-change: transform, top, left, opacity;
}

@keyframes fadeInHex {
  from {
    opacity: 0;
    transform: translateY(20px) scale(0.9);
  }
  to {
    opacity: 1;
    transform: translateY(0) scale(1);
  }
}
.big-hex.animate-in {
  opacity: 0;
  animation: fadeInHex 0.4s ease-out forwards;
}

@keyframes shake {
  10%, 90% { transform: translate3d(-1px, 0, 0); }
  20%, 80% { transform: translate3d(2px, 0, 0); }
  30%, 50%, 70% { transform: translate3d(-4px, 0, 0); }
  40%, 60% { transform: translate3d(4px, 0, 0); }
}
.modal.shake {
  animation: shake 0.82s cubic-bezier(.36,.07,.19,.97) both;
}

@keyframes celebrate-pop {
  0% { transform: scale(0.8); opacity: 0; }
  100% { transform: scale(1); opacity: 1; }
}
.modal.celebrate {
  animation: celebrate-pop 0.3s ease-out forwards;
}

/* NEW: Celebration Confetti (Replaces Mirror Shards) */
.celebration-container {
  position: fixed;
  inset: 0;
  pointer-events: none;
  z-index: 100;
}

.confetti-shard {
  position: absolute;
  top: 50%;
  left: 50%;
  width: 10px;
  height: 10px;
  background: var(--muted);
  opacity: 0;
  animation: confetti-pop-fall 3s ease-out forwards;
}

.confetti-shard.hex {
  clip-path: polygon(25% 0, 75% 0, 100% 50%, 75% 100%, 25% 100%, 0 50%);
  width: 12px;
  height: 14px;
}

.confetti-shard.gold {
  background: var(--gold);
}

@keyframes confetti-pop-fall {
  0% {
    transform: translate(-50%, -50%) scale(0) rotate(0deg);
    opacity: 1;
  }
  25% {
    opacity: 1;
  }
  100% {
    transform: var(--end-transform);
    opacity: 0;
  }
}

@media (max-width: 768px) {
  .app { flex-direction: column; }
}
`;

/* -------------------------
 * Sample quiz bank (small)
 * In production you will load a bigger JSON.
 * ------------------------- */
const MIRROR_QUIZ_BANK = {
  kids: [
    { id: "k1", q: "What is the primary purpose of the James Webb Space Telescope?", options: ["To study the Moon.", "To look at distant galaxies.", "To spy on Earth.", "To find aliens."], a: "To look at distant galaxies.", fact: "Correct! JWST is designed to see the very first stars and galaxies that formed in the early universe.", hint: "Think about what the telescope is designed to see far, far away." },
    { id: "k2", q: "How many mirrors does JWST have?", options: ["1", "5", "18", "100"], a: "18", fact: "That's right! JWST has 18 hexagonal mirror segments that work together as one large mirror.", hint: "It's a special number in this game! How many hexagons are there to unlock?" },
    { id: "k3", q: "What shape are the mirror segments?", options: ["Square", "Circle", "Hexagon", "Triangle"], a: "Hexagon", fact: "Yes! Hexagons are used because they fit together perfectly without gaps, like a honeycomb.", hint: "This shape is famous for being used by bees to build their honeycombs." },
    { id: "k4", q: "What is the name of the big sun-blocking shield on the telescope?", options: ["The Umbrella", "The Sunshield", "The Visor", "The Blanket"], a: "The Sunshield", fact: "Correct! The five-layer sunshield protects the telescope from the heat of the Sun, Earth, and Moon.", hint: "The name is very descriptive of what it does!" },
    { id: "k5", q: "What color is the thin coating on the mirrors?", options: ["Silver", "Bronze", "Gold", "Copper"], a: "Gold", fact: "You got it! The gold coating is excellent at reflecting infrared light, which is what the telescope uses to see distant objects.", hint: "It's a precious metal that is very shiny and yellow." },
    { id: "k6", q: "Where does the JWST orbit in space?", options: ["Near the Earth.", "Near the Sun.", "At L2 Lagrange Point.", "Near the Moon."], a: "At L2 Lagrange Point.", fact: "That's it! The L2 point is a special place in space where gravitational forces allow the telescope to stay in a stable position.", hint: "It's not near any planet, but at a special point in space where gravity is balanced." },
    { id: "k7", q: "What kind of light does the JWST primarily observe?", options: ["Ultraviolet light", "Visible light", "X-ray light", "Infrared light"], a: "Infrared light", fact: "Correct! Infrared light allows the telescope to see through cosmic dust clouds that block visible light.", hint: "This type of light is associated with heat, which is why the telescope needs to be so cold." },
    { id: "k8", q: "Is the JWST bigger or smaller than the Hubble Space Telescope?", options: ["Bigger", "Smaller", "Same size", "Cannot be compared"], a: "Bigger", fact: "Right! The JWST's mirror is much larger than Hubble's, allowing it to collect more light and see fainter objects.", hint: "The JWST can see much farther and fainter things, so it needs a... mirror." },
    { id: "k9", q: "What is a 'star nursery'?", options: ["A home for alien babies.", "A place where new stars are born.", "A school for astronauts.", "A part of a spaceship."], a: "A place where new stars are born.", fact: "Exactly! JWST is great at observing star nurseries because they are often shrouded in dust, which infrared light can penetrate.", hint: "What do you call a place where babies are cared for? Now apply that to stars." },
    { id: "k10", q: "What is a 'galaxy'?", options: ["A type of star.", "A small planet.", "A huge collection of stars, gas, and dust.", "A type of spaceship."], a: "A huge collection of stars, gas, and dust.", fact: "Correct! Our own galaxy, the Milky Way, contains billions of stars.", hint: "The Milky Way is one of these." },
    { id: "k11", q: "What is the name of the most famous image from the JWST?", options: ["The Sun.", "The Moon.", "The Pillars of Creation.", "The Space Dog."], a: "The Pillars of Creation.", fact: "Yes! The Pillars of Creation is a famous star-forming region, and JWST captured a stunning new image of it.", hint: "This famous cosmic structure looks like giant towers of gas and dust." },
    { id: "k12", q: "How many layers are in the JWST's sunshield?", options: ["1", "3", "5", "10"], a: "5", fact: "Correct! The five layers are made of a very thin material called Kapton and are designed to keep the telescope extremely cold.", hint: "It's a small odd number." },
    { id: "k13", q: "What is the 'Big Bang'?", options: ["A loud sound.", "The beginning of the universe.", "A type of star.", "A big explosion."], a: "The beginning of the universe.", fact: "That's right. JWST is designed to see the light from objects that formed just after the Big Bang.", hint: "This event is what scientists believe started everything." },
    { id: "k14", q: "What does 'NASA' stand for?", options: ["National Astronauts & Space Agency", "National Aeronautics and Space Administration", "New American Space Agency", "North Atlantic Space Alliance"], a: "National Aeronautics and Space Administration", fact: "Correct! NASA is the U.S. government agency responsible for space exploration.", hint: "The 'A's stand for Aeronautics and Administration." },
    { id: "k15", q: "What is the main material of the JWST mirrors?", options: ["Glass", "Plastic", "Steel", "Beryllium"], a: "Beryllium", fact: "Yes! Beryllium is a lightweight and very stable material, making it ideal for the telescope's mirrors.", hint: "It's a very strong but very light metal, its name starts with a 'B'." },
    { id: "k16", q: "How big is the main mirror of the JWST?", options: ["The size of a car.", "The size of a tennis court.", "The size of a house.", "The size of a small boat."], a: "The size of a tennis court.", fact: "Correct! The JWST's main mirror is about 6.5 meters (21 feet) across, roughly the size of a tennis court.", hint: "Think of a sport played on a rectangular court with a net." },
    { id: "k17", q: "Why does the JWST need to be so cold?", options: ["To keep the astronauts comfortable.", "To prevent the electronics from overheating.", "To observe infrared light from distant objects.", "To keep the food from spoiling."], a: "To observe infrared light from distant objects.", fact: "Exactly. Infrared is heat, so the telescope must be kept extremely cold to prevent its own heat from interfering with faint heat signals from space.", hint: "The telescope is looking for heat (infrared light), so its own heat would interfere." },
    { id: "k18", q: "Who is the JWST named after?", options: ["A famous scientist.", "A former NASA administrator.", "A fictional character.", "A planet."], a: "A former NASA administrator.", fact: "Correct. The telescope is named after James E. Webb, who was the second administrator of NASA and led the agency during the Apollo program.", hint: "He was a leader at NASA during the famous moon landing missions." }
  ],
  teens: [
    { id: "t1", q: "Which celestial objects are best observed by JWST's infrared capabilities?", options: ["Hot, young stars", "Cooler, redder objects and distant galaxies", "Planets in our solar system", "Black holes"], a: "Cooler, redder objects and distant galaxies", fact: "Correct. JWST is optimized to detect infrared light, which is emitted by cooler objects and light from the early universe stretched by cosmic expansion.", hint: "JWST is an infrared telescope, which is good for seeing things that aren't extremely hot and are very far away." },
    { id: "t2", q: "Why is the L2 Lagrange point an ideal orbit for JWST?", options: ["It is the closest point to Earth.", "It provides a stable gravitational point for a sun-synchronous orbit.", "It is the only place with no gravitational pull.", "It is a point where no space debris exists."], a: "It provides a stable gravitational point for a sun-synchronous orbit.", fact: "Exactly. At L2, JWST can stay in a relatively stable position with respect to the Earth and Sun, allowing the sunshield to be effective.", hint: "Think of a special spot where the gravity of the Sun and Earth balance out, letting the telescope stay put." },
    { id: "t3", q: "What is a 'gravitational lens'?", options: ["A type of camera lens.", "A phenomenon where gravity bends light from a distant object.", "A black hole.", "A theoretical space device."], a: "A phenomenon where gravity bends light from a distant object.", fact: "That's right. Massive objects like galaxy clusters can act as gravitational lenses, magnifying the light from objects behind them, which JWST can observe.", hint: "What does a lens do to light? Now imagine gravity doing that." },
    { id: "t4", q: "What is the main material of JWST's primary mirror segments?", options: ["Fused silica glass", "Aluminum alloy", "Beryllium", "Carbon fiber"], a: "Beryllium", fact: "Correct. Beryllium is chosen for its light weight and ability to maintain its shape at extremely low temperatures.", hint: "This lightweight metal is also used in aerospace for its thermal stability. It starts with 'B'." },
    { id: "t5", q: "Why is the mirror's gold coating so important?", options: ["For aesthetics", "To increase reflectivity of infrared light", "To prevent corrosion", "To reduce weight"], a: "To increase reflectivity of infrared light", fact: "Yes! Gold is an excellent reflector of infrared light, which is crucial for JWST's mission.", hint: "The telescope is designed to see infrared light. Which material is one of the best reflectors for this type of light?" },
    { id: "t6", q: "What is a 'nebula'?", options: ["A type of star.", "A cloud of gas and dust in space.", "A type of planet.", "A black hole."], a: "A cloud of gas and dust in space.", fact: "Correct. JWST's infrared vision allows it to see through nebulae to observe the stars and planets forming within.", hint: "Think of a cosmic cloud. The Orion ____ is a famous example." },
    { id: "t7", q: "What is the purpose of the Microshutter Array (MSA) on JWST?", options: ["To block sunlight.", "To take high-resolution images.", "To select individual objects for spectroscopy.", "To adjust the mirror segments."], a: "To select individual objects for spectroscopy.", fact: "Correct. The MSA contains over a quarter of a million tiny shutters that can be individually opened or closed to allow light from specific objects to enter the spectrograph.", hint: "This instrument needs to look at hundreds of distant objects at once. How can it select just one?" },
    { id: "t8", q: "What is the name of the first full-color image released by JWST?", options: ["Stephan's Quintet", "The Carina Nebula", "SMACS 0723", "The Orion Nebula"], a: "SMACS 0723", fact: "That's right. The image of galaxy cluster SMACS 0723 was the first full-color, deep-field image released from the telescope.", hint: "The name is a catalog number for a galaxy cluster that acts as a gravitational lens." },
    { id: "t9", q: "What is the primary scientific focus of JWST's MIRI instrument?", options: ["Observing visible light", "Studying exoplanets in the mid-infrared range", "Imaging Jupiter's storms", "Tracking asteroids"], a: "Studying exoplanets in the mid-infrared range", fact: "Correct. MIRI, the Mid-Infrared Instrument, is designed to study the light from exoplanets and distant galaxies.", hint: "MIRI stands for Mid-Infrared Instrument. What would that be good at studying?" },
    { id: "t10", q: "How did JWST deploy its sunshield after launch?", options: ["It unfolded automatically from a spring.", "It was deployed manually by astronauts.", "It was a complex process of motors and pulleys controlled from Earth.", "It was deployed using solar sails."], a: "It was a complex process of motors and pulleys controlled from Earth.", fact: "Correct. The deployment of the sunshield was one of the riskiest parts of the mission, involving 132 release mechanisms and 8 motors.", hint: "It was a very delicate and complex procedure that couldn't be done by hand in deep space." },
    { id: "t11", q: "What does 'redshift' mean in astronomy?", options: ["The shifting of light to a redder color due to cosmic expansion.", "The color of a star when it is born.", "A type of galaxy.", "The color of a planet's atmosphere."], a: "The shifting of light to a redder color due to cosmic expansion.", fact: "Yes! Redshift is a key concept that allows astronomers to measure the distance to galaxies and how fast they are moving away from us.", hint: "As the universe expands, light waves from distant objects get stretched out, shifting them towards which end of the spectrum?" },
    { id: "t12", q: "Why can't JWST observe from Earth's orbit like the Hubble?", options: ["It needs to be closer to the Sun.", "Earth's heat and light would interfere with its infrared observations.", "The orbit is too crowded.", "It would be too fast to capture images."], a: "Earth's heat and light would interfere with its infrared observations.", fact: "Correct. Earth and the Sun radiate infrared heat, which would blind JWST's sensitive instruments.", hint: "Infrared is essentially heat. What are two major sources of heat near our planet?" },
    { id: "t13", q: "How large is the sunshield's size?", options: ["Size of a bus", "Size of a car", "Size of a tennis court", "Size of a football field"], a: "Size of a tennis court", fact: "Correct. The sunshield is roughly the size of a tennis court and provides the necessary cooling for the telescope.", hint: "It needs to be large enough to block the Sun, Earth, and Moon's heat from the telescope." },
    { id: "t14", q: "What is the mission's primary scientific objective?", options: ["To find life on other planets", "To study the solar system", "To search for the first light in the universe", "To explore black holes"], a: "To search for the first light in the universe", fact: "Exactly. By observing the first light from the universe's oldest stars and galaxies, JWST helps us understand how the universe began.", hint: "The telescope is often called a 'time machine' because it can see..." },
    { id: "t15", q: "What is the term for the process of aligning the 18 mirror segments?", options: ["Automatic focusing", "Mirror polishing", "Wavefront sensing and control", "Segment bending"], a: "Wavefront sensing and control", fact: "Correct. This complex process involves taking images of a star and adjusting the mirrors millimeter by millimeter to act as a single, perfect reflector.", hint: "This process involves analyzing the 'wavefront' of light from a star to make tiny adjustments." },
    { id: "t16", q: "Which celestial object did JWST recently capture a new, high-resolution image of?", options: ["Pluto", "Uranus", "Neptune", "Jupiter"], a: "Neptune", fact: "That's right. JWST's infrared camera captured stunning new details of Neptune's rings and moons.", hint: "This ice giant is the eighth planet from the Sun and is known for its deep blue color." },
    { id: "t17", q: "What does JWST's NIRSpec instrument do?", options: ["Takes pictures in visible light.", "Measures the composition of distant objects.", "Acts as a shield.", "Collects radio waves."], a: "Measures the composition of distant objects.", fact: "Correct. NIRSpec (Near-Infrared Spectrograph) can analyze the light from up to 100 objects at once to determine their chemical composition, temperature, and motion.", hint: "NIRSpec breaks down light into its component colors, a process called spectroscopy, to learn about an object's..." },
    { id: "t18", q: "How was the JWST launched?", options: ["On a space shuttle.", "By a rocket.", "From a space station.", "It flew into space on its own."], a: "By a rocket.", fact: "Correct. The JWST was launched on an Ariane 5 rocket from Europe's Spaceport in French Guiana.", hint: "It needed a very powerful vehicle to escape Earth's gravity and travel to the L2 point." }
  ],
  adults: [
    { id: "a1", q: "What is the primary mirror's total effective light-collecting area in square meters?", options: ["25.4 m^2", "15.2 m^2", "30.4 m^2", "40.2 m^2"], a: "25.4 m^2", fact: "Correct. The total effective light-collecting area of the primary mirror is approximately 25.4 square meters, significantly larger than Hubble's.", hint: "It's significantly larger than Hubble's 4.5 m^2 mirror." },
    { id: "a2", q: "Which of these is NOT a scientific instrument on board JWST?", options: ["NIRCam", "NIRSpec", "MIRI", "Hubble"], a: "Hubble", fact: "Correct. Hubble is a separate space telescope. The JWST instruments are NIRCam, NIRSpec, FGS/NIRISS, and MIRI.", hint: "One of these is the predecessor to JWST, not an instrument on it." },
    { id: "a3", q: "What is the material used for the sunshield's layers?", options: ["Kapton", "Teflon", "Mylar", "Aluminum"], a: "Kapton", fact: "Correct. The sunshield's five layers are made of Kapton, a durable polyimide film, coated with aluminum and doped silicon.", hint: "This polyimide film is known for its thermal stability and is often used in flexible electronics and spacecraft." },
    { id: "a4", q: "What is the 'Webb's Law of Cosmic Expansion'?", options: ["A law about a fictional character.", "The rate at which the universe is expanding.", "A term for the telescope's mirror alignment.", "A term for the telescope's sunshield deployment."], a: "The rate at which the universe is expanding.", fact: "Correct, this is a trick question! While JWST helps refine our understanding of cosmic expansion, there is no such named law.", hint: "This is a trick question! While JWST studies cosmic expansion, there is no such named law." },
    { id: "a5", q: "What is the main advantage of JWST's cold operating temperature?", options: ["It prolongs the life of the instruments.", "It makes the electronics more efficient.", "It reduces background infrared noise from the telescope itself.", "It allows for faster data transfer."], a: "It reduces background infrared noise from the telescope itself.", fact: "Correct. The telescope must be kept at a frigid -233°C to prevent its own thermal radiation from overwhelming the faint infrared signals from deep space.", hint: "The telescope itself emits thermal radiation (infrared). To see faint signals, its own 'noise' must be minimized." },
    { id: "a6", q: "What is the primary purpose of JWST's Near-Infrared Camera (NIRCam)?", options: ["To study the atmospheres of exoplanets.", "To take high-resolution images in the near-infrared.", "To measure the redshift of distant galaxies.", "To track objects in our solar system."], a: "To take high-resolution images in the near-infrared.", fact: "Correct. NIRCam is JWST's primary imager and is used for everything from finding the first stars to imaging objects in our solar system.", hint: "NIRCam stands for Near-Infrared Camera. What is the primary function of a camera?" },
    { id: "a7", q: "What is the name of the final destination orbit of JWST?", options: ["Geostationary Orbit", "Low Earth Orbit", "L2 Lagrange Point", "Lunar Orbit"], a: "L2 Lagrange Point", fact: "Correct. The L2 point is approximately 1.5 million kilometers from Earth on the opposite side of the Sun.", hint: "This is a gravitationally stable point about 1.5 million km from Earth, away from the Sun." },
    { id: "a8", q: "What is the phenomenon called when a massive object, like a galaxy cluster, bends light from a distant source?", options: ["Light refraction", "Gravitational lensing", "Cosmic dispersion", "Spacetime warping"], a: "Gravitational lensing", fact: "Correct. Gravitational lensing allows JWST to see objects that would otherwise be too faint or distant.", hint: "Einstein's theory of general relativity predicted this effect." },
    { id: "a9", q: "What is a 'protostar'?", options: ["An ancient star.", "The beginning of a new star.", "A star that has died.", "A type of black hole."], a: "The beginning of a new star.", fact: "Correct. Protostars are stars in their infancy, still gathering mass from a surrounding molecular cloud, and they are best observed in the infrared spectrum.", hint: "The prefix 'proto-' means 'first' or 'early form of'." },
    { id: "a10", q: "What is the main advantage of the segmented primary mirror design?", options: ["It is cheaper to produce.", "It allows for a larger mirror that can be folded for launch.", "It provides better resolution.", "It is more resistant to damage."], a: "It allows for a larger mirror that can be folded for launch.", fact: "Correct. The segmented design was essential for fitting the massive mirror into the launch vehicle's fairing.", hint: "A single mirror of this size would be too large and heavy to fit inside any existing rocket fairing." },
    { id: "a11", q: "Which part of the electromagnetic spectrum does JWST's MIRI (Mid-Infrared Instrument) primarily operate in?", options: ["Visible light", "Mid-infrared", "Radio waves", "Gamma rays"], a: "Mid-infrared", fact: "Correct. MIRI's ability to see in the mid-infrared allows it to detect colder objects, like the dust clouds where stars and planets are born.", hint: "The name of the instrument gives it away: MIRI." },
    { id: "a12", q: "What is a 'supernova'?", options: ["A new star.", "An exploding star.", "A type of black hole.", "A large galaxy."], a: "An exploding star.", fact: "Correct. JWST can observe the remnants of supernovae, providing clues about star life cycles.", hint: "The prefix 'nova' means 'new', but 'supernova' refers to the spectacular death of a massive star." },
    { id: "a13", q: "How long will the JWST mission last?", options: ["5 years", "10 years", "20 years", "Indefinitely"], a: "10 years", fact: "Correct. The mission is expected to last for a minimum of 5.5 years, with an aspirational goal of 10 years or more, limited by onboard fuel.", hint: "The mission's duration is limited by the amount of fuel needed to maintain its orbit at L2." },
    { id: "a14", q: "What is the term for the complex process of deploying the telescope in space?", options: ["Unfolding", "Deployment", "Commissioning", "Alignment"], a: "Deployment", fact: "Correct. The deployment phase included the unfolding of the sunshield, secondary mirror, and primary mirror wings.", hint: "This is the general term for the entire process of getting the telescope from launch configuration to operational state." },
    { id: "a15", q: "What is the purpose of JWST's Fine Guidance Sensor (FGS)?", options: ["To find new planets.", "To track celestial objects with high precision.", "To take high-resolution images.", "To adjust the telescope's temperature."], a: "To track celestial objects with high precision.", fact: "Correct. The FGS is critical for keeping the telescope pointed at its target and for providing stable data collection.", hint: "To take stable, long-exposure images, the telescope needs a system to lock onto guide stars with extreme precision." },
    { id: "a16", q: "What does the 'Astro-photometry' scientific mode allow JWST to do?", options: ["Take pictures of the moon.", "Measure the brightness of objects in space.", "Measure the distance to stars.", "Create 3D models of galaxies."], a: "Measure the brightness of objects in space.", fact: "Correct. This mode allows scientists to accurately measure the brightness of celestial objects, which provides information about their temperature, composition, and distance.", hint: "The root 'photo' relates to light, and 'metry' relates to measurement." },
    { id: "a17", q: "Which type of exoplanet is JWST especially suited to observe and characterize?", options: ["Rocky planets", "Gas giants", "Hot Jupiters", "Habitable-zone planets with water"], a: "Habitable-zone planets with water", fact: "Correct. JWST's instruments are sensitive enough to analyze the atmospheres of exoplanets for signs of water vapor and other key molecules.", hint: "JWST can perform transmission spectroscopy, analyzing starlight passing through an exoplanet's atmosphere to detect molecules like..." },
    { id: "a18", q: "How many motors and release mechanisms were used to deploy the sunshield?", options: ["10 motors and 50 mechanisms", "5 motors and 100 mechanisms", "8 motors and 132 mechanisms", "20 motors and 200 mechanisms"], a: "8 motors and 132 mechanisms", fact: "Correct. The sunshield deployment was a high-stakes, choreographed sequence involving 8 deployment motors and 132 release mechanisms, with no room for error.", hint: "It was a famously complex deployment with over a hundred non-redundant release mechanisms." }
  ]
};

const STORAGE_KEY = "jwst_mirror_quest_v4";
const TOTAL_MIRRORS = 18;
const HEXES_PER_MIRROR = 18;

// Helper function to shuffle an array
function shuffleArray(array) {
  let currentIndex = array.length, randomIndex;
  while (currentIndex !== 0) {
    randomIndex = Math.floor(Math.random() * currentIndex);
    currentIndex--;
    [array[currentIndex], array[randomIndex]] = [array[randomIndex], array[currentIndex]];
  }
  return array;
}

function createInitialMirrors() {
  const mirrors = [];
  const kidsQuestionIds = MIRROR_QUIZ_BANK.kids.map(q => q.id);
  const teensQuestionIds = MIRROR_QUIZ_BANK.teens.map(q => q.id);
  const adultsQuestionIds = MIRROR_QUIZ_BANK.adults.map(q => q.id);

  for (let i = 0; i < TOTAL_MIRRORS; i++) {
    const mini = [];
    for (let j = 0; j < HEXES_PER_MIRROR; j++) {
      mini.push({ id: `${i}-${j}`, unlocked: false });
    }
    mirrors.push({
      id: i,
      mini,
      imageUrl: null,
      imageDescription: null,
      isGenerating: false,
      isGeneratingDescription: false,
      questionOrders: {
        kids: shuffleArray([...kidsQuestionIds]),
        teens: shuffleArray([...teensQuestionIds]),
        adults: shuffleArray([...adultsQuestionIds]),
      }
    });
  }
  return mirrors;
}

const getImagePrompt = (mirrorId) => {
  const prompts = [
    "A stunning, high-resolution photo of the Orion Nebula, filled with bright colors and swirling gas clouds, as if seen by the James Webb Space Telescope.",
    "A majestic, detailed image of the Pillars of Creation with a prominent cosmic dust cloud and glowing stars, as if seen by the James Webb Space Telescope.",
    "A breathtaking photo of the Carina Nebula, showing new stars being born in a giant cosmic cloud, as if seen by the James Webb Space Telescope.",
    "A vivid image of a spiral galaxy like Andromeda, with bright star-forming regions and a glowing core, as if seen by the James Webb Space Telescope.",
    "A beautiful, high-resolution photo of a distant galaxy cluster, showing gravitational lensing and ancient galaxies, as if seen by the James Webb Space Telescope.",
    "A detailed image of a star-forming region in the Milky Way, with bright young stars and dark dust lanes, as if seen by the James Webb Space Telescope.",
    "A cosmic cloud of glowing gas and dust, with a celestial body in the foreground, as if seen by the James Webb Space Telescope.",
    "A vibrant image of the Horsehead Nebula, highlighting its dark silhouette against a red background, as if seen by the James Webb Space Telescope.",
    "A detailed photo of a globular cluster, showing thousands of tightly packed stars, as if seen by the James Webb Space Telescope.",
    "A beautiful portrait of two merging galaxies, with tidal tails and chaotic star formations, as if seen by the James Webb Space Telescope.",
    "A serene, high-resolution image of a planetary nebula, showing the beautiful remnants of a dying star, as if seen by the James Webb Space Telescope.",
    "A captivating view of a star nursery, with glowing pillars and dust clouds, as if seen by the James Webb Space Telescope.",
    "A dynamic image of a supernova remnant, with expanding gas and glowing filaments, as if seen by the James Webb Space Telescope.",
    "A detailed photo of a galaxy's galactic center, with a massive black hole and swirling stars, as if seen by the James Webb Space Telescope.",
    "A vibrant image of a cosmic jet, shooting out from a young star or black hole, as if seen by the James Webb Space Telescope.",
    "A beautiful picture of a molecular cloud, with cold gas and dust collapsing to form new stars, as if seen by the James Webb Space Telescope.",
    "A stunning view of a star cluster, with different ages and colors of stars visible, as if seen by the James Webb Space Telescope.",
    "An intricate image of a cosmic spiderweb, with long filaments of gas and dark matter, as if seen by the James Webb Space Telescope."
  ];
  return prompts[mirrorId % prompts.length];
};

const miniHexPositions = [
  "0% 0%", "20% 0%", "40% 0%", "60% 0%", "80% 0%", "100% 0%",
  "0% 50%", "20% 50%", "40% 50%", "60% 50%", "80% 50%", "100% 50%",
  "0% 100%", "20% 100%", "40% 100%", "60% 100%", "80% 100%", "100% 100%",
];

function ImageAssemblyAnimation({ mirror, onComplete }) {
  const [isAssembling, setIsAssembling] = useState(false);

  useEffect(() => {
    const startTimer = setTimeout(() => setIsAssembling(true), 100);
    const completeTimer = setTimeout(() => {
        onComplete();
    }, 1800);

    return () => {
      clearTimeout(startTimer);
      clearTimeout(completeTimer);
    };
  }, [onComplete]);

  const initialPositions = useMemo(() => {
    return Array(HEXES_PER_MIRROR).fill(0).map(() => ({
      top: `${Math.random() * 100 - 50}vh`,
      left: `${Math.random() * 100 - 50}vw`,
      transform: `scale(${Math.random() * 1.5 + 0.5}) rotate(${Math.random() * 720 - 360}deg)`,
      opacity: 0,
    }));
  }, []);

  const finalPositions = useMemo(() => {
    const pieceWidthPercent = 100 / 6;
    const pieceHeightPercent = 100 / 3;
    return Array(HEXES_PER_MIRROR).fill(0).map((_, i) => {
      const col = i % 6;
      const row = Math.floor(i / 6);
      return {
        top: `${row * pieceHeightPercent}%`,
        left: `${col * pieceWidthPercent}%`,
        transform: 'scale(1) rotate(0deg)',
        opacity: 1,
      };
    });
  }, []);

  const assemblyHexPositions = useMemo(() => {
    return Array(HEXES_PER_MIRROR).fill(0).map((_, i) => {
      const col = i % 6;
      const row = Math.floor(i / 6);
      const x = (col / 5) * 100;
      const y = (row / 2) * 100;
      return `${x}% ${y}%`;
    });
  }, []);

  return (
    <div className="assembly-backdrop">
      <div className="assembly-container">
        {mirror.mini.map((_, index) => (
          <div
            key={index}
            className="assembly-piece"
            style={{
              backgroundImage: `url(${mirror.imageUrl})`,
              backgroundPosition: assemblyHexPositions[index],
              ...(isAssembling ? finalPositions[index] : initialPositions[index]),
            }}
          />
        ))}
      </div>
    </div>
  );
}

// NEW: Celebration Confetti Component
const CelebrationConfetti = () => {
    const shards = useMemo(() => {
      const pieces = [];
      const count = 150; // More confetti!
      for (let i = 0; i < count; i++) {
        const isHex = Math.random() > 0.5;
        const isGold = Math.random() > 0.4;
        const endX = (Math.random() - 0.5) * 2 * window.innerWidth;
        const endY = (Math.random() - 0.5) * 2 * window.innerHeight;
        const endRotate = Math.random() * 720 - 360;
        const endScale = Math.random() * 0.5 + 0.75;
        
        pieces.push({
          id: i,
          className: `confetti-shard ${isHex ? 'hex' : ''} ${isGold ? 'gold' : ''}`,
          style: {
            '--end-transform': `translate(${endX}px, ${endY}px) scale(${endScale}) rotate(${endRotate}deg)`,
            animationDelay: `${Math.random() * 0.2}s`,
            animationDuration: `${Math.random() * 1 + 2}s`, // 2s to 3s duration
          }
        });
      }
      return pieces;
    }, []);

    return (
      <div className="celebration-container">
        {shards.map(s => <div key={s.id} className={s.className} style={s.style} />)}
      </div>
    );
};

const SatelliteIcon = () => (
    <svg viewBox="0 0 100 40" fill="none" xmlns="http://www.w3.org/2000/svg" style={{ width: '100%', height: '100%', filter: 'drop-shadow(0 0 5px rgba(255,255,255,0.3))' }}>
        <rect x="0" y="10" width="25" height="20" fill="#4B5563"/>
        <rect x="75" y="10" width="25" height="20" fill="#4B5563"/>
        <path d="M30 15 H 70 V 25 H 30 Z" fill="#9CA3AF"/>
        <path d="M48 25 L 48 35 L 52 35 L 52 25 Z" fill="#FBBF24" />
    </svg>
);


/* -------------------------
 * App Component
 * ------------------------- */
export default function App() {
  useEffect(() => {
    const s = document.createElement("style");
    s.innerHTML = injectedCSS;
    document.head.appendChild(s);
    return () => { document.head.removeChild(s); };
  }, []);

  const [mirrors, setMirrors] = useState(() => {
    const saved = localStorage.getItem(STORAGE_KEY);
    if (saved) {
        try {
            const savedState = JSON.parse(saved);
            const loadedSavableMirrors = savedState.mirrors;

            if (loadedSavableMirrors && loadedSavableMirrors.length > 0) {
                return loadedSavableMirrors.map(sm => ({
                    ...sm,
                    imageUrl: null,
                    imageDescription: null,
                    isGenerating: false,
                    isGeneratingDescription: false,
                }));
            }
        } catch (e) {
            console.error("Failed to parse saved state:", e);
            localStorage.removeItem(STORAGE_KEY);
        }
    }
    return createInitialMirrors();
  });

  const [ageGroup, setAgeGroup] = useState(() => {
    const saved = localStorage.getItem(STORAGE_KEY);
    if (saved) {
        try {
            return JSON.parse(saved).ageGroup || null;
        } catch { return null; }
    }
    return null;
  });

  const [screen, setScreen] = useState(() => {
    const saved = localStorage.getItem(STORAGE_KEY);
    if (saved) {
        try {
            if (JSON.parse(saved).ageGroup) return "game";
        } catch { return "intro"; }
    }
    return "intro";
  });
  
  const [question, setQuestion] = useState(null);
  const [message, setMessage] = useState(null);
  const [confirm, setConfirm] = useState(null);
  const [revealedPiece, setRevealedPiece] = useState(null);
  const [correctAnswerFact, setCorrectAnswerFact] = useState(null);
  const [showFullImage, setShowFullImage] = useState(false);
  const [fullImageContent, setFullImageContent] = useState({ src: null, description: null, title: null });
  const [animatingMirror, setAnimatingMirror] = useState(null);
  const [animateHexGrid, setAnimateHexGrid] = useState(false);

  const firstIncompleteMirrorIndex = useMemo(() => mirrors.findIndex(m => !m.mini.every(x => x.unlocked)), [mirrors]);

  const [progress, setProgress] = useState(() => {
    const saved = localStorage.getItem(STORAGE_KEY);
    if (saved) {
      try {
        const obj = JSON.parse(saved);
        return obj.progress || { unlockedCount: 0, completedMirrors: 0 };
      } catch { return { unlockedCount: 0, completedMirrors: 0 }; }
    }
    return { unlockedCount: 0, completedMirrors: 0 };
  });

  const isInitialLoad = useRef(true);
  useEffect(() => {
    if (isInitialLoad.current) {
        isInitialLoad.current = false;
        return;
    }
    
    const savableMirrors = mirrors.map(mirror => ({
        id: mirror.id,
        mini: mirror.mini,
        questionOrders: mirror.questionOrders,
    }));

    try {
        localStorage.setItem(STORAGE_KEY, JSON.stringify({ mirrors: savableMirrors, progress, ageGroup }));
    } catch (error) {
        console.error("Failed to save game state:", error);
    }
  }, [mirrors, progress, ageGroup]);

  useEffect(() => {
    if (screen === 'game') {
        const timer = setTimeout(() => setAnimateHexGrid(true), 100);
        return () => clearTimeout(timer);
    } else {
        setAnimateHexGrid(false);
    }
  }, [screen]);


  const generateImageDescription = useCallback(async (mirrorId, imagePrompt) => {
    setMirrors(prev => prev.map((m, idx) => idx === mirrorId ? { ...m, isGeneratingDescription: true } : m));
    const prompt = `Write a short, educational paragraph about the following image description, suitable for all ages: "${imagePrompt}"`;
    const chatHistory = [{ role: "user", parts: [{ text: prompt }] }];
    const payload = { contents: chatHistory };
    const apiKey = "";
    const apiUrl = `https://generativelanguage.googleapis.com/v1beta/models/gemini-2.5-flash-preview-05-20:generateContent?key=${apiKey}`;

    try {
      const response = await fetch(apiUrl, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(payload)
      });
      const result = await response.json();
      if (result.candidates && result.candidates[0]?.content?.parts?.[0]?.text) {
        const text = result.candidates[0].content.parts[0].text;
        setMirrors(prev => prev.map((m, idx) => idx === mirrorId ? { ...m, imageDescription: text, isGeneratingDescription: false } : m));
      } else {
        console.error('Description generation failed: No content found.');
        setMirrors(prev => prev.map((m, idx) => idx === mirrorId ? { ...m, isGeneratingDescription: false } : m));
      }
    } catch (error) {
      console.error('API call error:', error);
      setMirrors(prev => prev.map((m, idx) => idx === mirrorId ? { ...m, isGeneratingDescription: false } : m));
    }
  }, []);

  const generateImage = useCallback(async (mirrorId) => {
    setMirrors(prev => prev.map((m, idx) => idx === mirrorId ? { ...m, isGenerating: true } : m));
    const prompt = getImagePrompt(mirrorId);
    const payload = { instances: { prompt: prompt }, parameters: { "sampleCount": 1 } };
    const apiKey = "";
    const apiUrl = `https://generativelanguage.googleapis.com/v1beta/models/imagen-3.0-generate-002:predict?key=${apiKey}`;

    try {
      const response = await fetch(apiUrl, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(payload)
      });
      const result = await response.json();
      if (result.predictions?.[0]?.bytesBase64Encoded && result.predictions[0].bytesBase64Encoded.length > 100) {
        const imageUrl = `data:image/png;base64,${result.predictions[0].bytesBase64Encoded}`;
        setMirrors(prev => prev.map((m, idx) => idx === mirrorId ? { ...m, imageUrl: imageUrl, isGenerating: false } : m));
        generateImageDescription(mirrorId, prompt);
      } else {
        console.error('Image generation failed: No valid predictions found.');
        setMessage({ title: "Image Generation Failed", text: "Could not generate an image at this time. Please try again later." });
        setMirrors(prev => prev.map((m, idx) => idx === mirrorId ? { ...m, isGenerating: false } : m));
      }
    } catch (error) {
      console.error('API call error:', error);
      setMessage({ title: "Image Generation Failed", text: "An error occurred while generating the image." });
      setMirrors(prev => prev.map((m, idx) => idx === mirrorId ? { ...m, isGenerating: false } : m));
    }
  }, [generateImageDescription]);

  const startMission = useCallback((level) => {
    const levelMap = { 'low': 'kids', 'medium': 'teens', 'hard': 'adults' };
    const group = levelMap[level];
    setAgeGroup(group);
    setScreen("game");
  }, []);

  const openMirrorForQuestion = useCallback((mirrorId) => {
    const mirror = mirrors[mirrorId];
    if (!mirror) return;
    if (!mirror.imageUrl && !mirror.isGenerating) {
      generateImage(mirrorId);
    }
    const nextMiniIndex = mirror.mini.findIndex(x => !x.unlocked);
    if (nextMiniIndex === -1) return;

    const currentAgeGroup = ageGroup || "kids";
    const quizBank = MIRROR_QUIZ_BANK[currentAgeGroup];
    const questionId = mirror.questionOrders[currentAgeGroup][nextMiniIndex];
    const q = quizBank.find(item => item.id === questionId);
    if (!q) {
      setMessage({ title: "Error", text: "Could not load the next question." });
      return;
    }
    setQuestion({ ...q, mirrorId, miniIndex: nextMiniIndex });
    setScreen("modal");
  }, [mirrors, ageGroup, generateImage]);

  const answerQuestion = useCallback((option) => {
    if (!question) return;
    const correct = option === question.a;
    const questionMirrorId = question.mirrorId;
    const questionMiniIndex = question.miniIndex;
    const questionFact = question.fact;

    setQuestion(null);
    setScreen("game");

    if (correct) {
        setMirrors(prevMirrors => {
            const newMirrors = prevMirrors.map(m => ({ ...m, mini: m.mini.map(x => ({ ...x })) }));
            const currentMirror = newMirrors[questionMirrorId];
            if(currentMirror) {
                currentMirror.mini[questionMiniIndex].unlocked = true;
            }
            
            const totalUnlocked = newMirrors.reduce((acc, it) => acc + it.mini.filter(t => t.unlocked).length, 0);
            const completedMirrors = newMirrors.filter(it => it.mini.every(h => h.unlocked)).length;
            setProgress({ unlockedCount: totalUnlocked, completedMirrors });

            if (newMirrors.every(m => m.mini.every(h => h.unlocked))) {
                setTimeout(() => setScreen("complete"), 150);
            }
            
            return newMirrors;
        });

        setCorrectAnswerFact({
            fact: questionFact,
            pieceInfo: {
              imageUrl: mirrors[questionMirrorId].imageUrl,
              miniIndex: questionMiniIndex,
              mirrorId: questionMirrorId,
            }
        });
    } else {
      setMessage({ title: "Try Again!", text: question.hint || "That's not correct. Try again!", shake: true });
    }
  }, [question, mirrors]);

  const handleCloseRevealedPiece = useCallback(() => {
    const mirror = mirrors[revealedPiece.mirrorId];
    setRevealedPiece(null);
    if (mirror && mirror.mini.every(x => x.unlocked)) {
      setAnimatingMirror(mirror);
    }
  }, [mirrors, revealedPiece]);

  const playAgain = useCallback(() => {
    setConfirm({
      text: "Restart mission and clear all progress?",
      onConfirm: () => {
        localStorage.removeItem(STORAGE_KEY);
        setMirrors(createInitialMirrors());
        setProgress({ unlockedCount: 0, completedMirrors: 0 });
        setAgeGroup(null);
        setScreen("intro");
        setConfirm(null);
      },
      onCancel: () => setConfirm(null)
    });
  }, []);

  const handleBack = useCallback(() => {
    if (screen === 'game') setScreen('levels');
    else if (screen === 'levels') setScreen('start');
    else if (screen === 'start') setScreen('intro');
  }, [screen]);

  const percent = Math.round((progress.unlockedCount / (TOTAL_MIRRORS * HEXES_PER_MIRROR)) * 100);

  return (
    <>
      <div className="background-gradient"></div>
      <div id="stars"></div>
      <div id="stars2"></div>
      <div id="stars3"></div>
      <div id="twinkling-stars"></div>
      <div className="comet"></div>
      <div className="comet" style={{ left: '20%', animationDelay: '3s', animationDuration: '12s' }}></div>
      <div className="comet" style={{ left: '80%', animationDelay: '1.5s', animationDuration: '18s' }}></div>
      <div className="satellite"><SatelliteIcon /></div>
      <div className="satellite satellite-2"><SatelliteIcon /></div>
      
      <div style={{ padding: 18, position: 'relative', zIndex: 1 }}>
        <div className="app">
          <div className="left">
            <div className="header">
                <div style={{ flex: 1, display: 'flex' }}>
                    {(screen === "game" || screen === "levels" || screen === "start") && (
                        <button className="btn" onClick={handleBack}>Back</button>
                    )}
                </div>
                <div className="title" style={{ flex: 2 }}>
                    🔭 HexaLens
                </div>
                <div className="controls" style={{ flex: 1, justifyContent: 'flex-end' }}>
                    {(screen === "game" || screen === "levels" || screen === "start") && (
                        <button className="btn small" onClick={playAgain}>Restart</button>
                    )}
                    {screen === "complete" && (
                        <button className="btn primary" onClick={playAgain}>Play Again</button>
                    )}
                </div>
            </div>

            {(screen === "game" || screen === "complete") && (
              <div style={{ marginBottom: 12 }}>
                <div style={{ display: "flex", justifyContent: "space-between", alignItems: "center" }}>
                  <div style={{ fontSize: 14, color: '#e6eef8' }}>Progress: {progress.unlockedCount} / {TOTAL_MIRRORS * HEXES_PER_MIRROR} mini-hex unlocked</div>
                  <div style={{ fontSize: 13, color: "#9aa4b2" }}>Completed mirrors: {progress.completedMirrors} / {TOTAL_MIRRORS}</div>
                </div>
                <div className="progress" style={{ marginTop: 8 }}><div style={{ width: `${percent}%` }} /></div>
              </div>
            )}
            
            {screen === "intro" && (
              <div className="intro-screen">
                <h2>The James Webb Space Telescope</h2>
                <p className="hint" style={{maxWidth: '600px', lineHeight: 1.6}}>
                  Welcome, Mission Specialist! You are about to embark on a journey to align the most powerful space telescope ever built. Launched in 2021, the <b>James Webb Space Telescope (JWST)</b> is an infrared observatory orbiting the Sun a million miles from Earth. Its massive, 18-segment gold-coated mirror allows it to peer back in time to see the first stars and galaxies, uncover the secrets of star birth, and study the atmospheres of distant planets.
                </p>
                <button className="btn primary" onClick={() => setScreen("start")}>Continue</button>
              </div>
            )}

            {screen === "start" && (
              <div className="start-screen">
                <h2>Mission Brief</h2>
                <p className="hint">Your mission is to align the James Webb Space Telescope's 18 primary mirror segments. Each segment is a puzzle that you unlock by answering questions about space and the JWST. Complete all 18 mirrors to reveal stunning cosmic images and complete the alignment.</p>
                <button className="btn primary" onClick={() => setScreen("levels")}>Start Mission</button>
              </div>
            )}

            {screen === "levels" && (
              <div className="level-selection">
                <h2>Select Difficulty</h2>
                <button className="btn primary" onClick={() => startMission('low')}>Easy</button>
                <button className="btn primary" onClick={() => startMission('medium')}>Medium</button>
                <button className="btn primary" onClick={() => startMission('hard')}>Hard</button>
              </div>
            )}

            {screen === "game" && (
              <div className="honey-wrap">
                {[mirrors.slice(0, 3), mirrors.slice(3, 7), mirrors.slice(7, 12), mirrors.slice(12, 16), mirrors.slice(16, 18)].map((row, rowIndex) => (
                  <div key={rowIndex} className="hex-row">
                    {row.map((m) => {
                      const complete = m.mini.every((x) => x.unlocked);
                      const isLocked = firstIncompleteMirrorIndex !== -1 && m.id > firstIncompleteMirrorIndex;

                      const handleMirrorClick = (mirror) => {
                        if (complete) {
                          setAnimatingMirror(mirror);
                          return;
                        }
                        if (isLocked) {
                          setMessage({
                            title: "Mirror Locked",
                            text: `Please complete Mirror ${firstIncompleteMirrorIndex + 1} to unlock this one.`
                          });
                          return;
                        }
                        openMirrorForQuestion(mirror.id);
                      };

                      return (
                        <div 
                          key={m.id} 
                          className={`big-hex ${animateHexGrid ? 'animate-in' : ''}`} 
                          onClick={() => handleMirrorClick(m)} 
                          style={{ 
                            cursor: isLocked ? "not-allowed" : "pointer",
                            ...(animateHexGrid && { animationDelay: `${m.id * 50}ms` })
                          }}
                        >
                          <div
                            className={`hex-shape ${complete ? "hex-complete" : isLocked ? "hex-truly-locked" : "hex-locked"}`}
                            style={complete && m.imageUrl ? { backgroundImage: `url(${m.imageUrl})` } : {}}
                          >
                            {!complete && (
                              <>
                                <div style={{ textAlign: "center", position: "relative", zIndex: 10 }}>
                                  <div style={{ fontSize: 14, fontWeight: 700 }}>
                                    {`Mirror ${m.id + 1}`}
                                  </div>
                                  <div style={{ fontSize: 12, marginTop: 6 }}>
                                    {isLocked
                                      ? "(Locked)"
                                      : m.isGenerating || m.isGeneratingDescription
                                      ? "Generating..."
                                      : `${m.mini.filter((x) => x.unlocked).length}/${HEXES_PER_MIRROR}`
                                    }
                                  </div>
                                </div>
                                {m.imageUrl && (
                                  <div className="mini-grid">
                                    {m.mini.map((tile, idx) => (<div key={tile.id} className="mini-hex-piece" style={{ opacity: tile.unlocked ? 1 : 0, backgroundImage: `url(${m.imageUrl})`, backgroundPosition: miniHexPositions[idx] }} />))}
                                  </div>
                                )}
                              </>
                            )}
                          </div>
                        </div>
                      );
                    })}
                  </div>
                ))}
              </div>
            )}

            {screen === "modal" && question && (
              <div className="modal-backdrop">
                <div className="modal">
                  <div style={{ display: "flex", justifyContent: "space-between", alignItems: "center" }}>
                    <div className="question">{question.q}</div>
                    <div style={{ color: "#9aa4b2" }}>Mirror {question.mirrorId + 1} • Tile {question.miniIndex + 1}</div>
                  </div>
                  <div className="options">
                    {question.options.map((opt, idx) => (<button key={idx} className="option-btn" onClick={() => answerQuestion(opt)}>{opt}</button>))}
                  </div>
                  <div style={{ marginTop: 12, display: "flex", justifyContent: "flex-end" }}><button className="btn small" onClick={() => { setQuestion(null); setScreen("game"); }}>Close</button></div>
                </div>
              </div>
            )}

            {screen === "complete" && (
              <div style={{ padding: 20 }}>
                <h2>🎉 Mission Complete — JWST Aligned!</h2>
                <p className="hint">You've unlocked all mirror segments. Congratulations — you now understand the mirror alignment challenge JWST engineers solved!</p>
                <div style={{ marginTop: 12 }}><button className="btn primary" onClick={() => setMessage({ title: "Share Feature", text: "The share feature is not implemented in this demo." })}>Share your achievement</button></div>
              </div>
            )}
          </div>
        </div>

        {message && (
          <div className="modal-backdrop">
            <div className={`modal ${message.shake ? 'shake' : ''}`} style={{ width: "400px", padding: "20px" }}>
              <div style={{ fontWeight: 700, fontSize: "1.2rem", marginBottom: "10px" }}>{message.title}</div>
              <p>{message.text}</p>
              <div style={{ marginTop: "20px", textAlign: "right" }}><button className="btn" onClick={() => setMessage(null)}>Close</button></div>
            </div>
          </div>
        )}
        
        {correctAnswerFact && <CelebrationConfetti />}
        {correctAnswerFact && (
          <div className="modal-backdrop">
            <div className="modal celebrate" style={{ width: "500px", padding: "20px" }}>
              <h3 style={{ color: "var(--gold)", marginTop: 0 }}>Correct!</h3>
              <p className="fact" style={{ background: 'transparent', padding: 0, margin: 0 }}>{correctAnswerFact.fact}</p>
              <div style={{ marginTop: "20px", textAlign: "right" }}>
                <button className="btn primary" onClick={() => { setRevealedPiece(correctAnswerFact.pieceInfo); setCorrectAnswerFact(null); }}>Reveal Piece</button>
              </div>
            </div>
          </div>
        )}

        {confirm && (
          <div className="modal-backdrop">
            <div className="modal" style={{ width: "400px", padding: "20px" }}>
              <div style={{ fontWeight: 700, fontSize: "1.2rem", marginBottom: "10px" }}>Confirm</div>
              <p>{confirm.text}</p>
              <div style={{ marginTop: "20px", display: "flex", justifyContent: "flex-end", gap: "10px" }}>
                <button className="btn" onClick={confirm.onCancel}>Cancel</button>
                <button className="btn primary" onClick={confirm.onConfirm}>Confirm</button>
              </div>
            </div>
          </div>
        )}

        {revealedPiece && (
          <div className="modal-backdrop">
            <div className="piece-reveal-modal">
              <h3>Piece Unlocked!</h3>
              <div className="piece-img-container">
                <div className="mini-hex-piece" style={{ width: "100%", height: "100%", backgroundImage: `url(${revealedPiece.imageUrl})`, backgroundPosition: miniHexPositions[revealedPiece.miniIndex], opacity: 1 }} />
              </div>
              <button className="btn small" onClick={handleCloseRevealedPiece}>Awesome!</button>
            </div>
          </div>
        )}

        {showFullImage && fullImageContent.src && (
          <div className="modal-backdrop">
            <div className="full-image-modal">
              <button className="close-btn" onClick={() => setShowFullImage(false)}>X</button>
              <div className="full-image-content">
                <img src={fullImageContent.src} alt={`Full Cosmic Image`} />
                {fullImageContent.description ? (<p className="full-image-description">{fullImageContent.description}</p>) : (<p className="full-image-description">Generating description...</p>)}
              </div>
            </div>
          </div>
        )}

        {animatingMirror && (
          <ImageAssemblyAnimation
            mirror={animatingMirror}
            onComplete={() => {
              setFullImageContent({ src: animatingMirror.imageUrl, description: animatingMirror.imageDescription, title: getImagePrompt(animatingMirror.id) });
              setShowFullImage(true);
              setAnimatingMirror(null);
            }}
          />
        )}
      </div>
    </>
  );
}
