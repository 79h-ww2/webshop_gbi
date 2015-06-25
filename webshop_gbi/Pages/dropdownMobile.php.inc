     	<?php
									$navi = new Navigation ();
									$arr_kategorie = $navi->erstelle_array_kategorien ();
									
									for($i = 0; $i < count ( $arr_kategorie ); $i ++) {
										$kategorie = $arr_kategorie [$i];
										 if ($i == 0) {
											echo '<ul>';
											
											$bauart = $navi->erstelle_array_bauart ();
											$z = 0;
											foreach ( $bauart as $b ) {
												if ($z == 0)
													echo '<div class="Spalte">';
												echo '<li><a class="Untermenu" href="./?page=uebersicht&PTId=' . htmlspecialchars ( $kategorie->PTId, ENT_QUOTES, 'UTF-8' ) . '&bauart=' . htmlspecialchars ( $b->BId, ENT_QUOTES, 'UTF-8' ) . '">' . htmlspecialchars ( $b->Bezeichnung, ENT_QUOTES, 'UTF-8' ) . '</a></li>';
												if ($z == 3) {
													echo '</div>';
													$z = - 1;
												}
												$z ++;
											}
											if ($z < 3)
												echo '</div>';
											
											echo '</ul>';
										}
									}
									?>